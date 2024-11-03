#include "Camden.h" // Include Camden header file.

#include "Enums.h" // Include Enums for predefined enumerations.
#include "Grid.h" // Include Grid for handling game grid operations.
#include "Player.h" // Include Player class for player interactions.

#include <string> // Include string class.
    using std::string; // Use string from standard namespace.

#include <vector> // Include vector class for dynamic arrays.
    using std::vector; // Use vector from standard namespace.

#include <stdexcept> // Include standard exceptions for error handling.
    using std::out_of_range; // Use out_of_range for boundary checking.
    using std::logic_error; // Use logic_error for logical exceptions.

#include <iostream> // Include for input-output operations.
    using std::cout; // Use cout for console output.
    using std::cin; // Use cin for console input.

// Method: Checks if a ship was just sunk by comparing the size of the numShipsSank vector.
bool Camden::did_just_sink_ship() const {
    return this->numShipsSank[this->numShipsSank.size() - 1] != this->numShipsSank[this->numShipsSank.size() - 2];
}

// Method: Checks if a given space is available in the availableSpaces vector.
bool Camden::space_is_available(string space) const {
    for(string avail_space : this->availableSpaces)
        if(avail_space == space)
            return true;
    return false;
}

// Method: Initializes Camden by setting up available spaces and attack directions.
void Camden::set_Camden() {
    for(string space : Spaces::spaceStrings) // Populate available spaces.
        this->availableSpaces.push_back(space);
    for(char direction : this->directions) // Populate initial attack directions.
        this->attackDirections.push_back(direction);
}

// Method: Resets Camden's state to default values.
void Camden::reset_to_default() {
    this->firstAttackSpace = "";
    this->lastAttackSpace = "";
    this->attackDirection = ' ';
    this->isAttackingShip = false;
    this->attackSpaces.clear(); // Clear attack spaces vector.
    this->attackDirections.clear(); // Clear attack directions vector.
    for(char direction : this->directions) // Restore initial directions.
        this->attackDirections.push_back(direction);
}

// Method: Switches the current attack direction to its opposite.
void Camden::switch_direction_to_opposite() {
    switch(this->attackDirection) {
        case 'N': this->attackDirection = 'S'; break;
        case 'S': this->attackDirection = 'N'; break;
        case 'E': this->attackDirection = 'W'; break;
        case 'W': this->attackDirection = 'E'; break;
        default: return; // Do nothing if no valid direction is set.
    }
}

// Method: Updates the numShipsSank vector to include the number of sunk ships of the opponent.
void Camden::update_num_ships_sank() {
    this->numShipsSank.push_back(static_cast<int>(this->self->getFoe()->getSunkenShips().size()));
}

// Method: Identifies and removes spaces with no viable neighbors (holes).
void Camden::check_for_holes() {
    vector<string> holes; // Vector to store identified holes.
    int good_neighbor_count; // Counter for good neighboring spaces.
    for(string space : this->availableSpaces) {
        good_neighbor_count = 0; // Reset count for each space.
        for(char direction : this->directions){
            try {
                string neighbor = Grid::goDirection(space, direction); // Get neighboring space.
                if (this->space_is_available(neighbor))
                    ++good_neighbor_count; // Increment if valid neighbor.
            }
            catch(out_of_range& e) { // Ignore out of range errors.
                continue;
            }
        }
        if(!good_neighbor_count) // If no valid neighbors found, mark as a hole.
            holes.push_back(space);
    }
    this->remove_available_spaces(holes); // Remove identified holes from available spaces.
}

// Method: Initiates an attack from a specific space.
void Camden::initiate_attack(string space) {
    this->isAttackingShip = true; // Set attacking state.
    this->firstAttackSpace = space; // Set the first attack space.
    this->lastAttackSpace = space; // Set the last attack space.
    this->attackSpaces.push_back(space); // Add space to attack spaces vector.
}

// Method: Removes a specific attack direction from attackDirections vector.
void Camden::remove_attack_direction(char direction) {
    for(size_t i = 0; i < this->attackDirections.size(); ++i)
        if(this->attackDirections[i] == direction) {
            this->attackDirections.erase(this->attackDirections.begin() + i); // Remove direction.
            break;
        }
}

// Method: Removes a specific space from availableSpaces vector.
void Camden::remove_available_space(string space) {
    for (size_t i = 0; i < this->availableSpaces.size(); ++i)
        if(this->availableSpaces[i] == space) {
            this->availableSpaces.erase(this->availableSpaces.begin() + i); // Remove space.
            break;
        }
}

// Method: Removes multiple spaces from availableSpaces vector.
void Camden::remove_available_spaces(vector<string> spaces) {
    for(string space : spaces)
        this->remove_available_space(space); // Remove each space.
}

// Method: Switches direction to its opposite and resets last attack space to first.
void Camden::do_switch() {
    this->switch_direction_to_opposite(); // Change direction to opposite.
    this->lastAttackSpace = this->firstAttackSpace; // Reset last attack space.
}

// Method: Checks if a space contains a part of a ship (stud).
bool Camden::is_a_hit(string space) const {
    return this->foeGrid->getSpace(space)->hasStud(); // Return true if space has a stud.
}

// Method: Picks a new attack direction and checks its validity.
string Camden::pick_direction(int(*rand_func)(), char& direction) {
    string new_space; // New space to attack.
    do {
        direction = this->attackDirections[static_cast<size_t>(rand_func() % this->attackDirections.size())]; // Randomly select direction.
        try {
            string& tentative_new_space = new_space;
            tentative_new_space = Grid::goDirection(this->firstAttackSpace, direction); // Get new space in chosen direction.
            if(this->space_is_available(new_space))
                break; // Break if space is available.
            else
                this->remove_attack_direction(direction); // Remove direction if not valid.
        }
        catch(out_of_range& e) { // Handle out of range exception.
            this->remove_attack_direction(direction); // Remove invalid direction.
            continue;
        }
    } while(this->attackDirections.size()); // Repeat until directions are exhausted.
    if(!new_space.length())
        throw new logic_error("All directions exhausted."); // Throw error if no valid space found.
    return new_space; // Return valid space.
}

// Method: Picks the next attack space based on the current attack state.
string Camden::pick_attack_space(int(*rand_func)()) {
    string new_space; // New space to attack.
    char rand_direction; // Random direction chosen.
    if(this->attackSpaces.size() == 1) { // If only one attack space.
        new_space = this->pick_direction(rand_func, rand_direction); // Pick a direction.
        if(this->is_a_hit(new_space)) { // Check if it is a hit.
            this->attackDirection = rand_direction; // Set attack direction.
            this->lastAttackSpace = new_space; // Update last attack space.
            this->attackSpaces.push_back(new_space); // Add to attack spaces.
        } else {
            this->remove_attack_direction(rand_direction); // Remove direction if not a hit.
        }
    } else { // If more than one attack space exists.
        try {
            new_space = Grid::goDirection(this->lastAttackSpace, this->attackDirection); // Get next space in current direction.
        } catch(out_of_range& e) { // Handle out of range exception.
            this->do_switch(); // Switch to opposite direction.
            new_space = Grid::goDirection(this->lastAttackSpace, this->attackDirection); // Get new space in switched direction.
        }
        if(this->is_a_hit(new_space)) { // Check if it is a hit.
            this->lastAttackSpace = new_space; // Update last attack space.
            this->attackSpaces.push_back(new_space); // Add to attack spaces.
        } else {
            this->do_switch(); // Switch direction if not a hit.
        }
    }
    this->update_num_ships_sank(); // Update number of ships sank.
    if(this->did_just_sink_ship()) { // If a ship was just sunk.
        this->remove_available_spaces(this->attackSpaces); // Remove attack spaces from available spaces.
        this->remove_available_spaces(Grid::neighborSpaces(this->attackSpaces)); // Remove neighboring spaces.
        this->check_for_holes(); // Check for holes.
        this->reset_to_default(); // Reset attack state.
    }
    return new_space; // Return chosen space.
}

// Method: Picks a random space to attack.
string Camden::pick_random_space(int(*rand_func)()) {
    string new_space = this->availableSpaces[static_cast<size_t>(rand_func() % this->availableSpaces.size())]; // Pick a random space.
    if(this->is_a_hit(new_space)) // Check if it is a hit.
        this->initiate_attack(new_space); // Initiate attack if a hit.
    else 
        this->remove_available_space(new_space); // Remove space if not a hit.
    this->update_num_ships_sank(); // Update number of ships sank.
    return new_space; // Return chosen space.
}

// Constructor: Default.
Camden::Camden() {}

// Constructor: Initializes Camden with a given player.
Camden::Camden(Player* the_self) : self{the_self}
{
    this->foeGrid = the_self->getFoeGrid(); // Set foe's grid.
    this->set_Camden(); // Initialize Camden.
}

// Destructor: Cleans up Camden object.
Camden::~Camden() {
    this->self = nullptr; // Set self to nullptr.
    this->foeGrid = nullptr; // Set foe grid to nullptr.
}

// Method: Makes a move by either continuing an attack or picking a random space.
string Camden::makeMove(int(*rand_func)()) {
    if(this->isAttackingShip)
        return this->pick_attack_space(rand_func); // Continue attack if attacking a ship.
    else
        return this->pick_random_space(rand_func); // Pick random space otherwise.
}
