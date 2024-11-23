#include "Destroyer.h"
#include "Ship.h"

#include "Enums.h"  // For enumerations like ShipType, PlayerType, and StudName.
#include "Grid.h"   // For handling grid-related operations.
#include "Stud.h"   // For managing the Destroyer's studs.

#include <string>
    using std::string; // For string manipulation.
#include <array>
    using std::array;  // Fixed-size array for the Destroyer's studs.
#include <stdexcept>
    using std::out_of_range; // Exception handling for invalid grid placements.
#include <iostream>
    using std::cout;
    using std::endl;

// **Default Constructor**
// Initializes a Destroyer without associating it with any player or grid.
Destroyer::Destroyer() : Ship(ShipType::DESTROYER) {}

// **Player-Specific Constructor**
// Creates a Destroyer for a specific player (e.g., CPU or human).
Destroyer::Destroyer(PlayerType of_player) : Ship(ShipType::DESTROYER, of_player) {}

// **Grid-Specific Constructor**
// Creates a Destroyer and associates it with a grid.
Destroyer::Destroyer(Grid* on_grid) : Ship(ShipType::DESTROYER, on_grid) 
{
    this->setStuds(); // Initializes the studs for the Destroyer.
}

// **Full Constructor**
// Creates a Destroyer, initializes its studs, and attempts to place it on the grid.
Destroyer::Destroyer(Grid* on_grid, string start_space, char direction) : Ship (ShipType::DESTROYER, on_grid)
{
    this->setStuds(); // Initializes the studs.
    this->isReady = this->placeOnGrid(start_space, direction); // Attempts placement on the grid.
}

// **Destructor**
// Cleans up dynamically allocated memory for the Destroyer's studs.
Destroyer::~Destroyer() {
    for(size_t i = 0; i < 3; ++i) {
        delete this->studs[i]; // Free memory for each stud.
        this->studs[i] = nullptr; // Set the pointer to nullptr for safety.
    }
}

// **Getter for All Studs**
// Returns an array of pointers to the Destroyer's studs.
array<Stud*, 3> Destroyer::getStuds() const {
    return this->studs;
}

// **Getter for a Specific Stud**
// Returns a specific stud based on its name.
Stud* Destroyer::getStud(StudName stud_name) const {
    for(Stud* stud : this->studs) {
        if(stud->getStudName() == stud_name) // Match the stud by its name.
            return stud;
    }
    return nullptr; // Return nullptr if no matching stud is found.
}

// **Check if a Stud Belongs to the Destroyer**
// Verifies whether the given stud is part of the Destroyer.
bool Destroyer::hasStud(Stud* stud) const {
    for(Stud* the_stud : this->studs) {
        if(the_stud == stud) // Compare pointers to identify the stud.
            return true;
    }
    return false; // Return false if the stud does not belong to the Destroyer.
}

// **Set Up Studs**
// Dynamically allocates and initializes the studs for the Destroyer.
void Destroyer::setStuds() {
    for(size_t i = 9, j = 0; i < 12; i++, j++) { // Destroyer uses studs indexed from 9 to 11.
        this->studs[j] = new Stud(Studs::studNames[i], this->ofPlayer, this); // Create new studs dynamically.
        this->intactStuds.push_back(this->studs[j]); // Add the stud to the list of intact studs.
    }
}

// **Place Destroyer on the Grid**
// Tries to place the Destroyer starting at a given space and direction.
// Returns true if the placement is successful; otherwise, false.
bool Destroyer::placeOnGrid(string start_space, char direction, bool print_out) const {
    vector<string> ship_spaces; // Stores the grid spaces that the Destroyer will occupy.
    try {
        // Calculate the grid spaces required for the Destroyer.
        ship_spaces = Grid::getVector(start_space, direction, 2); // Destroyer has a length of 3 (2 additional spaces from the start).
    } catch (out_of_range& e) {
        // Handle cases where placement goes out of the grid's boundaries.
        if(print_out)
            cout << "Out of range." << endl;
        return false; // Placement failed.
    }

    // Check if the spaces are already occupied or adjacent to other ships.
    if(this->onGrid->hasNoGoSpace(ship_spaces)) {
        if(print_out)
            cout << "Ships cannot be touching." << endl;
        return false; // Placement failed.
    }

    // Place the Destroyer's studs on the grid.
    for(size_t i = 0; i < 3; i++) 
        this->onGrid->setOnSpace(ship_spaces[i], this->studs[i]);

    // Mark neighboring spaces as no-go zones to prevent overlapping with other ships.
    vector<string> ship_neighbors = Grid::neighborSpaces(ship_spaces);
    this->onGrid->addNoGoSpaces(ship_spaces);    // Add the Destroyer's spaces to the no-go zones.
    this->onGrid->addNoGoSpaces(ship_neighbors); // Add neighboring spaces to the no-go zones.

    return true; 
}
