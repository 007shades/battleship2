#include "Camden.h"  // Includes the Camden class header file.

#include "Enums.h"   // Includes enumerations used in the class.
#include "Grid.h"    // Includes the Grid class, which manages the game board.
#include "Player.h"  // Includes the Player class.

#include <string>    // Provides the string class.
    using std::string;

#include <vector>    // Provides the vector container.
    using std::vector;

#include <stdexcept> // Provides standard exceptions like out_of_range and logic_error.
    using std::out_of_range;
    using std::logic_error;

#include <iostream>  // Provides input/output utilities.
    using std::cout;
    using std::cin;
    using std::endl;

// Checks if a ship was just sunk using the numShipsSank vector (method 1).
bool Camden::did_just_sink_ship_check1() const {
    return this->numShipsSank[this->numShipsSank.size() - 1] != this->numShipsSank[this->numShipsSank.size() - 2];
}

// Checks if the current victim ship was just sunk and the status hasn't been updated (method 2).
bool Camden::did_just_sink_ship_check2() const {
    return this->curVictimShip->wasSunk() && !this->hasSunkShip;
}

// Determines if a ship was just sunk using either of the two checks.
bool Camden::did_just_sink_ship() const {
    return this->did_just_sink_ship_check1() || this->did_just_sink_ship_check2();
}

// Checks if a specific space is available for selection.
bool Camden::space_is_available(string space) const {
    for (string avail_space : this->availableSpaces)
        if (avail_space == space)
            return true;
    return false;
}

// Initializes the Camden object with all possible spaces and directions.
void Camden::set_Camden() {
    for (string space : Spaces::spaceStrings)
        this->availableSpaces.push_back(space);
    for (char direction : this->directions)
        this->attackDirections.push_back(direction);
}

// Switches the current attack direction to its opposite.
void Camden::switch_direction_to_opposite() {
    switch (this->attackDirection) {
        case 'N': this->attackDirection = 'S'; break;
        case 'S': this->attackDirection = 'N'; break;
        case 'E': this->attackDirection = 'W'; break;
        case 'W': this->attackDirection = 'E'; break;
        default: return;
    }
}

// Updates the numShipsSank vector with the current count of sunken ships.
void Camden::update_num_ships_sank() {
    int num_ships_sank = static_cast<int>(this->self->getFoe()->getSunkenShips().size());
    this->numShipsSank.push_back(num_ships_sank);
}

// Removes "holes" (spaces with no valid neighbors) from availableSpaces.
void Camden::check_for_holes() {
    vector<string> holes;
    int good_neighbor_count;
    for (string space : this->availableSpaces) {
        good_neighbor_count = 0; // Reset counter.
        for (char direction : this->directions) {
            try {
                string neighbor = Grid::goDirection(space, direction);
                if (this->space_is_available(neighbor))
                    ++good_neighbor_count;
            } catch (out_of_range& e) {
                continue;
            }
        }
        if (!good_neighbor_count)
            holes.push_back(space);
    }
    this->remove_available_spaces(holes);
}

// Initiates an attack on a given space.
void Camden::initiate_attack(string space) {
    this->isAttackingShip = true;
    this->curVictimShip = this->foeGrid->getSpace(space)->getStud()->getOfShip();
    this->firstAttackSpace = space;
    this->lastAttackSpace = space;
    this->attackSpaces.push_back(space);
}

// Removes a specific attack direction from the list of possible directions.
void Camden::remove_attack_direction(char direction) {
    for (size_t i = 0; i < this->attackDirections.size(); ++i)
        if (this->attackDirections[i] == direction) {
            this->attackDirections.erase(this->attackDirections.begin() + i);
            break;
        }
}

// Removes a specific space from the availableSpaces vector.
void Camden::remove_available_space(string space) {
    for (size_t i = 0; i < this->availableSpaces.size(); ++i)
        if (this->availableSpaces[i] == space) {
            this->availableSpaces.erase(this->availableSpaces.begin() + i);
            break;
        }
}

// Removes multiple spaces from the availableSpaces vector.
void Camden::remove_available_spaces(vector<string> spaces) {
    for (string space : spaces)
        this->remove_available_space(space);
}

// Resets the attack state to its default values.
void Camden::reset_to_default() {
    this->firstAttackSpace = "";
    this->lastAttackSpace = "";
    this->attackDirection = ' ';
    this->isAttackingShip = false;
    this->hasSunkShip = false;
    this->curVictimShip = nullptr;
    this->remove_available_spaces(this->attackSpaces);
    this->remove_available_spaces(Grid::neighborSpaces(this->attackSpaces));
    this->check_for_holes();
    this->attackSpaces.clear();
    this->attackDirections.clear();
    for (char direction : this->directions)
        this->attackDirections.push_back(direction);
}

// Switches to the opposite attack direction and resets the last attack space.
void Camden::do_switch() {
    this->switch_direction_to_opposite();
    this->lastAttackSpace = this->firstAttackSpace;
}

// Checks if a given space is a hit (contains a stud).
bool Camden::is_a_hit(string space) const {
    return this->foeGrid->getSpace(space)->hasStud();
}

// Picks a direction and attempts to find a valid space to attack.
string Camden::pick_direction(int(*rand_func)(), char& direction) {
    string new_space;
    do {
        direction = this->attackDirections[static_cast<size_t>(rand_func() % this->attackDirections.size())];
        try {
            string& tentative_new_space = new_space;
            tentative_new_space = Grid::goDirection(this->firstAttackSpace, direction);
            if (this->space_is_available(new_space))
                break;
            else
                this->remove_attack_direction(direction);
        } catch (out_of_range& e) {
            this->remove_attack_direction(direction);
            continue;
        }
    } while (this->attackDirections.size());
    if (!new_space.length())
        throw logic_error("All directions exhausted.");
    return new_space;
}

// Picks a space to attack, either using the current strategy or by resetting.
string Camden::pick_attack_space(int(*rand_func)()) {
    string new_space;
    char rand_direction;
    if (this->did_just_sink_ship()) {
        this->reset_to_default();
        return "sunky";
    }
    if (this->attackSpaces.size() == 1) {
        new_space = this->pick_direction(rand_func, rand_direction);
        if (this->is_a_hit(new_space)) {
            this->attackDirection = rand_direction;
            this->lastAttackSpace = new_space;
            this->attackSpaces.push_back(new_space);
        } else {
            this->remove_attack_direction(rand_direction);
        }
    } else {
        try {
            new_space = Grid::goDirection(this->lastAttackSpace, this->attackDirection);
        } catch (out_of_range& e) {
            this->do_switch();
            new_space = Grid::goDirection(this->lastAttackSpace, this->attackDirection);
        }
        if (this->is_a_hit(new_space)) {
            this->lastAttackSpace = new_space;
            this->attackSpaces.push_back(new_space);
        } else {
            this->do_switch();
        }
    }
    this->update_num_ships_sank();
    if (this->did_just_sink_ship())
        this->reset_to_default();
    return new_space;
}

// Picks a random space to attack when no specific strategy is active.
string Camden::pick_random_space(int(*rand_func)()) {
    string new_space = this->availableSpaces[static_cast<size_t>(rand_func() % this->availableSpaces.size())];
    if (this->is_a_hit(new_space))
        this->initiate_attack(new_space);
    else 
        this->remove_available_space(new_space);
    this->update_num_ships_sank();
    return new_space;
}

// Default constructor for Camden.
Camden::Camden() {}

// Constructor that initializes Camden with a Player object.
Camden::Camden(Player* the_self) : self{the_self} {
    this->foeGrid = the_self->getFoeGrid();
    this->set_Camden();
}

// Destructor cleans up resources used by Camden.
Camden::~Camden() {
    this->self = nullptr;
    this->foeGrid = nullptr;
}

// Decides the next move, either using the attack strategy or randomly.
string Camden::makeAMove(int(*rand_func)()) {
    if (this->isAttackingShip) {
        string attack_space = this->pick_attack_space(rand_func);
        if (attack_space == "sunky")
            return this->pick_random_space(rand_func);
        else
            return attack_space;
    } else {
        return this->pick_random_space(rand_func);
    }
}

// Marks a space as invalid for attack.
void Camden::badBoy(string space) {
    this->remove_available_space(space);
}

// Combines strategy-based and manual move-making logic.
string Camden::makeMove(int(*rand_func)(), string space) {
    if (!(space == "" || space == "NA"))
        this->badBoy(space);
    return this->makeAMove(rand_func);
}
