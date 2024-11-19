#include "Destroyer.h" // Includes the Destroyer class header file.
#include "Ship.h"      // Includes the base Ship class header file.

#include "Enums.h"     // Includes enumerations such as ShipType and PlayerType.
#include "Grid.h"      // Includes the Grid class for managing the game board.
#include "Stud.h"      // Includes the Stud class, representing individual ship components.

#include <string>      // Provides the string class.
    using std::string;

#include <array>       // Provides the array container class.
    using std::array;

#include <stdexcept>   // Provides standard exceptions like out_of_range.
    using std::out_of_range;

#include <iostream>    // Provides input/output utilities.
    using std::cout;
    using std::endl;

// Default constructor initializes a Destroyer with its type as DESTROYER.
Destroyer::Destroyer() : Ship(ShipType::DESTROYER) {}

// Constructor initializes a Destroyer for a specific player.
Destroyer::Destroyer(PlayerType of_player) : Ship(ShipType::DESTROYER, of_player) {}

// Constructor places the Destroyer on a grid and initializes its components (studs).
Destroyer::Destroyer(Grid* on_grid) : Ship(ShipType::DESTROYER, on_grid) {
    this->setStuds(); // Initializes the studs array for the Destroyer.
}

// Constructor places the Destroyer on a grid, sets its studs, and attempts to place it on the grid.
Destroyer::Destroyer(Grid* on_grid, string start_space, char direction) : Ship(ShipType::DESTROYER, on_grid) {
    this->setStuds(); // Initializes the studs array.
    this->isReady = this->placeOnGrid(start_space, direction); // Places the ship on the grid.
}

// Destructor cleans up dynamically allocated Stud objects.
Destroyer::~Destroyer() {
    for (size_t i = 0; i < 3; ++i) {
        delete this->studs[i]; // Deletes each Stud object.
        this->studs[i] = nullptr; // Sets pointers to nullptr to avoid dangling references.
    }
}

// Getter for the array of Stud pointers.
array<Stud*, 3> Destroyer::getStuds() const {
    return this->studs;
}

// Retrieves a specific Stud by its name.
Stud* Destroyer::getStud(StudName stud_name) const {
    for (Stud* stud : this->studs)
        if (stud->getStudName() == stud_name) // Checks if the Stud's name matches.
            return stud; // Returns the matching Stud.
    return nullptr; // Returns nullptr if not found.
}

// Checks if a specific Stud is part of the Destroyer.
bool Destroyer::hasStud(Stud* stud) const {
    for (Stud* the_stud : this->studs)
        if (the_stud == stud) // Compares pointers to find the Stud.
            return true;
    return false;
}

// Initializes the Studs array with specific Stud objects.
void Destroyer::setStuds() {
    for (size_t i = 9, j = 0; i < 12; i++, j++) {
        this->studs[j] = new Stud(Studs::studNames[i], this->ofPlayer, this); // Creates new Stud objects.
        this->intactStuds.push_back(this->studs[j]); // Adds each Stud to the intactStuds list.
    }
}

// Attempts to place the Destroyer on the grid starting at a specific space and direction.
bool Destroyer::placeOnGrid(string start_space, char direction, bool print_out) const {
    vector<string> ship_spaces; // Stores the spaces the ship will occupy.
    try {
        ship_spaces = Grid::getVector(start_space, direction, 2); // Gets the spaces based on start and direction.
    } catch (out_of_range& e) {
        if (print_out)
            cout << "Out of range." << endl; // Prints an error if the placement is out of range.
        return false; // Placement failed.
    }
    if (this->onGrid->hasNoGoSpace(ship_spaces)) { // Checks if spaces are restricted.
        if (print_out)
            cout << "Ships cannot be touching." << endl; // Prints an error if the spaces are invalid.
        return false; // Placement failed.
    }
    for (size_t i = 0; i < 3; i++)
        this->onGrid->setOnSpace(ship_spaces[i], this->studs[i]); // Places each Stud in its respective space.
    vector<string> ship_neighbors = Grid::neighborSpaces(ship_spaces); // Gets neighboring spaces.
    this->onGrid->addNoGoSpaces(ship_spaces); // Marks the ship's spaces as restricted.
    this->onGrid->addNoGoSpaces(ship_neighbors); // Marks the neighboring spaces as restricted.
    return true; // Placement succeeded.
}
