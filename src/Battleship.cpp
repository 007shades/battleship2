#include "Battleship.h" // Includes the Battleship class header file.
#include "Ship.h"       // Includes the base Ship class header file.

#include "Enums.h"      // Includes enumerations for ShipType, PlayerType, etc.
#include "Grid.h"       // Includes the Grid class, managing the game board.
#include "Stud.h"       // Includes the Stud class, representing individual components of a ship.

#include <string>       // Provides the string class.
    using std::string;

#include <array>        // Provides the array container class.
    using std::array;

#include <stdexcept>    // Provides standard exceptions like out_of_range.
    using std::out_of_range;

#include <iostream>     // Provides input/output utilities.
    using std::cout;
    using std::endl;

// Default constructor initializes a Battleship with its type as BATTLESHIP.
Battleship::Battleship() : Ship(ShipType::BATTLESHIP) {}

// Constructor initializes a Battleship for a specific player.
Battleship::Battleship(PlayerType of_player) : Ship(ShipType::BATTLESHIP, of_player) {}

// Constructor places the Battleship on a grid and initializes its components (studs).
Battleship::Battleship(Grid* on_grid) : Ship(ShipType::BATTLESHIP, on_grid) 
{
    this->setStuds(); // Initializes the studs array for the battleship.
}

// Constructor places the Battleship on a grid, sets its studs, and attempts to place it on the grid.
Battleship::Battleship(Grid* on_grid, string start_space, char direction) : Ship(ShipType::BATTLESHIP, on_grid)
{
    this->setStuds(); // Initializes the studs array.
    this->isReady = this->placeOnGrid(start_space, direction); // Places the ship on the grid.
}

// Destructor cleans up dynamically allocated Stud objects.
Battleship::~Battleship() {
    for(size_t i = 0; i < 4; ++i) {
        delete this->studs[i]; // Deletes each Stud object.
        this->studs[i] = nullptr; // Sets pointers to nullptr to avoid dangling references.
    }
} 

// Getter for the array of Stud pointers.
array<Stud*, 4> Battleship::getStuds() const {
    return this->studs;
}

// Retrieves a specific Stud by its name.
Stud* Battleship::getStud(StudName stud_name) const {
    for(Stud* stud : this->studs)
        if(stud->getStudName() == stud_name) // Checks if the Stud's name matches.
            return stud; // Returns the matching Stud.
    return nullptr; // Returns nullptr if not found.
}

// Checks if a specific Stud is part of the Battleship.
bool Battleship::hasStud(Stud* stud) const {
    for(Stud* the_stud : this->studs)
        if(the_stud == stud) // Compares pointers to find the Stud.
            return true;
    return false;
}

// Initializes the Studs array with specific Stud objects.
void Battleship::setStuds() {
    for(size_t i=5, j=0; i<9; i++, j++){
        this->studs[j] = new Stud(Studs::studNames[i], this->ofPlayer, this); // Creates new Stud objects.
        this->intactStuds.push_back(this->studs[j]); // Adds each Stud to the intactStuds list.
    }
}

// Attempts to place the Battleship on the grid starting at a specific space and direction.
bool Battleship::placeOnGrid(string start_space, char direction, bool print_out) const {
    vector<string> ship_spaces; // Stores the spaces the ship will occupy.
    try {
        ship_spaces = Grid::getVector(start_space, direction, 3); // Gets the spaces based on start and direction.
    } catch (out_of_range& e) {
        if(print_out)
            cout << "Out of range." << endl; // Prints an error if the placement is out of range.
        return false; // Placement failed.
    }
    if(this->onGrid->hasNoGoSpace(ship_spaces)) { // Checks if spaces are restricted.
        if(print_out)
            cout << "Ships cannot be touching." << endl; // Prints an error if the spaces are invalid.
        return false; // Placement failed.
    }
    for(size_t i = 0; i < 4; i++)
        this->onGrid->setOnSpace(ship_spaces[i], this->studs[i]); // Places each Stud in its respective space.
    vector<string> ship_neighbors = Grid::neighborSpaces(ship_spaces); // Gets neighboring spaces.
    this->onGrid->addNoGoSpaces(ship_spaces); // Marks the ship's spaces as restricted.
    this->onGrid->addNoGoSpaces(ship_neighbors); // Marks the neighboring spaces as restricted.
    return true; // Placement succeeded.
}
