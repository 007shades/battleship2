#include "Submarine.h"
#include "Ship.h"

#include "Enums.h"  // For enums like ShipType, PlayerType, StudName, etc.
#include "Grid.h"   // For managing ship placement on a grid.
#include "Stud.h"   // For handling the submarine's individual sections.

#include <string>
    using std::string;

#include <array>
    using std::array;

#include <stdexcept>
    using std::out_of_range;

#include <iostream>
    using std::cout;
    using std::endl;

// ** Constructors **

// Default constructor: Initializes a submarine with its type.
Submarine::Submarine() : Ship(ShipType::SUBMARINE) {}

// Initializes a submarine with its type and owner.
Submarine::Submarine(PlayerType of_player) : Ship(ShipType::SUBMARINE, of_player) {}

// Initializes a submarine with its type and associates it with a grid.
Submarine::Submarine(Grid* on_grid) : Ship(ShipType::SUBMARINE, on_grid) 
{
    this->setStuds(); // Sets the submarine's studs.
}

// Initializes a submarine, associates it with a grid, and places it on the grid.
Submarine::Submarine(Grid* on_grid, string start_space, char direction) 
    : Ship(ShipType::SUBMARINE, on_grid)
{
    this->setStuds(); // Sets the submarine's studs.
    this->isReady = this->placeOnGrid(start_space, direction); // Attempts to place it on the grid.
}

// Destructor: Cleans up dynamically allocated memory for studs.
Submarine::~Submarine() {
    for (size_t i = 0; i < 3; ++i) {
        delete this->studs[i];
        this->studs[i] = nullptr;
    }
}

// ** Accessors **

// Returns the array of studs (sections) of the submarine.
array<Stud*, 3> Submarine::getStuds() const {
    return this->studs;
}

// Returns a specific stud by its name.
Stud* Submarine::getStud(StudName stud_name) const {
    for (Stud* stud : this->studs) {
        if (stud->getStudName() == stud_name) {
            return stud;
        }
    }
    return nullptr;
}

// Checks if a specific stud belongs to the submarine.
bool Submarine::hasStud(Stud* stud) const {
    for (Stud* the_stud : this->studs) {
        if (the_stud == stud) {
            return true;
        }
    }
    return false;
}

// ** Stud Initialization **

// Initializes the submarine's studs, associating them with this submarine and its owner.
void Submarine::setStuds() {
    for (size_t i = 12, j = 0; i < 15; i++, j++) { // Studs 12 to 14 are assigned to the submarine.
        this->studs[j] = new Stud(Studs::studNames[i], this->ofPlayer, this);
        this->intactStuds.push_back(this->studs[j]); // Adds the stud to the intact list.
    }
}

// ** Grid Placement **

// Attempts to place the submarine on the grid.
bool Submarine::placeOnGrid(string start_space, char direction, bool print_out) const {
    vector<string> ship_spaces;
    try {
        // Get a vector of grid spaces the submarine will occupy (3 spaces, including the start space).
        ship_spaces = Grid::getVector(start_space, direction, 2);
    } catch (out_of_range& e) {
        if (print_out) {
            cout << "Out of range." << endl;
        }
        return false; // Placement failed due to invalid position.
    }

    // Check if any of the target spaces or their neighbors are already occupied or restricted.
    if (this->onGrid->hasNoGoSpace(ship_spaces)) {
        if (print_out) {
            cout << "Ships cannot be touching." << endl;
        }
        return false; // Placement failed due to collision with another ship.
    }

    // Place the submarine's studs on the grid.
    for (size_t i = 0; i < 3; i++) {
        this->onGrid->setOnSpace(ship_spaces[i], this->studs[i]);
    }

    // Add the submarine's occupied spaces and their neighbors to the "no-go" list.
    vector<string> ship_neighbors = Grid::neighborSpaces(ship_spaces);
    this->onGrid->addNoGoSpaces(ship_spaces);
    this->onGrid->addNoGoSpaces(ship_neighbors);

    return true; // Placement succeeded.
}
