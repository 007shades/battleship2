#include "Camden.h"

#include "Enums.h"  // For enumerations like PlayerType and TargetResult.
#include "Grid.h"   // To interact with the grid system of the game.
#include "Player.h" // For managing player-specific operations.

#include <string>
    using std::string;
#include <vector>
    using std::vector;
#include <stdexcept>
    using std::out_of_range;
    using std::logic_error;
#include <iostream>
    using std::cout;
    using std::cin;
    using std::endl;

// ** Checks if a ship was just sunk (Condition 1) **
// Compares the latest count of sunk ships to the previous count.
// If the counts differ, a new ship has been sunk.
bool Camden::did_just_sink_ship_check1() const {
    return this->numShipsSank[this->numShipsSank.size() - 1] != 
           this->numShipsSank[this->numShipsSank.size() - 2];
}

// ** Checks if a ship was just sunk (Condition 2) **
// Evaluates whether the current target ship was sunk during this turn.
// Ensures the `hasSunkShip` flag has not yet been updated.
bool Camden::did_just_sink_ship_check2() const {
    return this->curVictimShip->wasSunk() && !this->hasSunkShip;
}

// ** Consolidated Sinking Check **
// Combines the two checks to determine if a ship was sunk this turn.
bool Camden::did_just_sink_ship() const {
    return this->did_just_sink_ship_check1() || this->did_just_sink_ship_check2();
}

// ** Validates Space Availability **
// Confirms if a given space is in the list of attackable spaces.
// Returns `true` if the space can be targeted, otherwise `false`.
bool Camden::space_is_available(string space) const {
    for (const string& avail_space : this->availableSpaces) {
        if (avail_space == space) {
            return true;
        }
    }
    return false;
}

// ** Initializes Camden's State **
// Populates the list of available spaces (all grid spaces) and
// attack directions (`N`, `S`, `E`, `W`).
void Camden::set_Camden() {
    for (const string& space : Spaces::spaceStrings) {
        this->availableSpaces.push_back(space);
    }
    for (char direction : this->directions) {
        this->attackDirections.push_back(direction);
    }
}

// ** Reverses the Current Attack Direction **
// Used when Camden needs to switch its attack pattern to the opposite direction.
void Camden::switch_direction_to_opposite() {
    switch (this->attackDirection) {
        case 'N':
            this->attackDirection = 'S'; // North → South
            break;
        case 'S':
            this->attackDirection = 'N'; // South → North
            break;
        case 'E':
            this->attackDirection = 'W'; // East → West
            break;
        case 'W':
            this->attackDirection = 'E'; // West → East
            break;
        default:
            return; // No valid direction.
    }
}

// ** Updates Sunk Ships History **
// Tracks the number of ships sunk by the opponent at the current turn.
// This helps Camden decide whether a ship was just sunk.
void Camden::update_num_ships_sank() {
    int num_ships_sank = static_cast<int>(this->self->getFoe()->getSunkenShips().size());
    this->numShipsSank.push_back(num_ships_sank);
}

// ** Removes Isolated Spaces from Attack List **
// Identifies spaces with no adjacent attackable neighbors and removes them.
// These spaces are "holes" in the attack grid and are unlikely to contain ships.
void Camden::check_for_holes() {
    vector<string> holes; // List of isolated spaces to be removed.
    int good_neighbor_count; // Count of valid neighbors for each space.
    for (const string& space : this->availableSpaces) {
        good_neighbor_count = 0;
        for (char direction : this->directions) {
            try {
                // Check the neighbor in the given direction.
                string neighbor = Grid::goDirection(space, direction);
                if (this->space_is_available(neighbor)) {
                    ++good_neighbor_count;
                }
            } catch (out_of_range&) {
                // Ignore out-of-bound neighbors.
                continue;
            }
        }
        if (good_neighbor_count == 0) {
            holes.push_back(space); // Mark isolated spaces for removal.
        }
    }
    this->remove_available_spaces(holes); // Remove all isolated spaces.
}

// ** Starts Targeting a Ship **
// Marks the start of an attack sequence on a specific ship.
void Camden::initiate_attack(string space) {
    this->isAttackingShip = true; // Flag to indicate an ongoing attack.
    this->curVictimShip = this->foeGrid->getSpace(space)->getStud()->getOfShip(); // Set target ship.
    this->firstAttackSpace = space; // Record the first hit space.
    this->lastAttackSpace = space; // Initialize the last hit space.
    this->attackSpaces.push_back(space); // Add the space to the attack history.
}

// ** Removes an Attack Direction **
// Deletes a direction from the list of potential attack paths.
void Camden::remove_attack_direction(char direction) {
    for (size_t i = 0; i < this->attackDirections.size(); ++i) {
        if (this->attackDirections[i] == direction) {
            this->attackDirections.erase(this->attackDirections.begin() + i);
            break;
        }
    }
}

// ** Removes a Space from Available Spaces **
// Deletes the specified space from Camden's list of targetable spaces.
void Camden::remove_available_space(string space) {
    for (size_t i = 0; i < this->availableSpaces.size(); ++i) {
        if (this->availableSpaces[i] == space) {
            this->availableSpaces.erase(this->availableSpaces.begin() + i);
            break;
        }
    }
}

// ** Removes Multiple Spaces from Available Spaces **
// Calls `remove_available_space` for each space in the given list.
void Camden::remove_available_spaces(vector<string> spaces) {
    for (const string& space : spaces) {
        this->remove_available_space(space);
    }
}

// ** Resets Camden's Attack State **
// Clears the current attack state and prepares Camden for the next attack sequence.
// Updates available spaces and resets attack directions.
void Camden::reset_to_default() {
    this->firstAttackSpace = ""; // Clear first attack space.
    this->lastAttackSpace = "";  // Clear last attack space.
    this->attackDirection = ' '; // Reset attack direction.
    this->isAttackingShip = false; // No active ship being targeted.
    this->hasSunkShip = false;     // Reset sunk ship flag.
    this->curVictimShip = nullptr; // Clear current victim ship.
    this->remove_available_spaces(this->attackSpaces); // Remove used attack spaces.
    this->remove_available_spaces(Grid::neighborSpaces(this->attackSpaces)); // Remove neighboring spaces.
    this->check_for_holes(); // Check for isolated spaces to remove.
    this->attackSpaces.clear(); // Clear attack history.
    this->attackDirections.clear(); // Reset attack directions.
    for (char direction : this->directions) {
        this->attackDirections.push_back(direction); // Re-add directions.
    }
}

// ** Reverses Direction During an Attack **
// Used when Camden needs to attack in the opposite direction from the current path.
void Camden::do_switch() {
    this->switch_direction_to_opposite(); // Reverse the direction.
    this->lastAttackSpace = this->firstAttackSpace; // Reset the last attack space.
}

// ** Checks if a Space Contains a Ship's Stud **
// Returns `true` if the space contains a ship part, otherwise `false`.
bool Camden::is_a_hit(string space) const {
    return this->foeGrid->getSpace(space)->hasStud();
}

// ** Picks a Random Direction for Attack **
// Chooses a new direction to attack, ensuring it is valid and within bounds.
string Camden::pick_direction(int(*rand_func)(), char& direction) {
    string new_space; // Holds the new attack space.
    do {
        direction = this->attackDirections[static_cast<size_t>(rand_func() % this->attackDirections.size())];
        try {
            string& tentative_new_space = new_space;
            tentative_new_space = Grid::goDirection(this->firstAttackSpace, direction); // Calculate the new space.
            if (this->space_is_available(new_space)) {
                break; // Valid space found.
            } else {
                this->remove_attack_direction(direction); // Remove invalid direction.
            }
        } catch (out_of_range&) {
            this->remove_attack_direction(direction); // Handle out-of-bound directions.
            continue;
        }
    } while (this->attackDirections.size());
    if (new_space.empty()) {
        throw logic_error("All directions exhausted."); // No valid directions remain.
    }
    return new_space;
}
