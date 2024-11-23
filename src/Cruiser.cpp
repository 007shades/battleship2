#include "Cruiser.h"
#include "Ship.h"

#include "Enums.h"     // For enumerations like ShipType and PlayerType.
#include "Grid.h"      // For handling the grid placement of ships.
#include "Stud.h"      // For managing the Cruiser's studs.

#include <string>
    using std::string; // For managing strings related to spaces.
#include <array>
    using std::array;  // Fixed-size array for the Cruiser's studs.
#include <stdexcept>
    using std::out_of_range; // Exception handling for grid operations.
#include <iostream>
    using std::cout;
    using std::endl;

// **Default Constructor**
// Initializes a Cruiser without any specific player or grid assignment.
Cruiser::Cruiser() : Ship(ShipType::CRUISER) {}

// **Player-Specific Constructor**
// Initializes a Cruiser for a specific player.
Cruiser::Cruiser(PlayerType of_player) : Ship(ShipType::CRUISER, of_player) {}

// **Grid-Specific Constructor**
// Initializes a Cruiser and associates it with a grid.
Cruiser::Cruiser(Grid* on_grid) : Ship(ShipType::CRUISER, on_grid) 
{
    this->setStuds(); // Set up the Cruiser's studs.
}

// **Full Constructor**
// Initializes a Cruiser, sets its studs, and attempts to place it on the grid.
Cruiser::Cruiser(Grid* on_grid, string start_space, char direction) : Ship(ShipType::CRUISER, on_grid)
{
    this->setStuds(); // Set up the studs for the Cruiser.
    this->isReady = this->placeOnGrid(start_space, direction); // Try to place the Cruiser on the grid.
}

// **Destructor**
// Cleans up dynamically allocated memory for the Cruiser's studs.
Cruiser::~Cruiser() {
    for(size_t i = 0; i < 2; ++i) {
        delete this->studs[i]; // Free memory for each stud.
        this->studs[i] = nullptr; // Set the pointer to nullptr.
    }
}

// **Getter for All Studs**
// Returns the array of pointers to the Cruiser's studs.
array<Stud*, 2> Cruiser::getStuds() const {
    return this->studs;
}

// **Getter for a Specific Stud**
// Finds and returns a specific stud by its name.
Stud* Cruiser::getStud(StudName stud_name) const {
    for(Stud* stud : this->studs)
        if(stud->getStudName() == stud_name) // Match the stud by its name.
            return stud;
    return nullptr; // Return nullptr if no match is found.
}

// **Check if a Stud Belongs to the Cruiser**
// Verifies if the given stud is part of the Cruiser.
bool Cruiser::hasStud(Stud* stud) const {
    for(Stud* the_stud : this->studs)
        if(the_stud == stud) // Compare pointers to identify the stud.
            return true;
    return false; // Return false if the stud is not part of the Cruiser.
}

// **Set Up Studs**
// Creates and initializes the Cruiser's studs.
void Cruiser::setStuds() {
    for(size_t i = 15, j = 0; i < 17; i++, j++) { // Cruiser uses studs indexed from 15 to 16.
        this->studs[j] = new Stud(Studs::studNames[i], this->ofPlayer, this); // Create new studs dynamically.
        this->intactStuds.push_back(this->studs[j]); // Add the new stud to the list of intact studs.
    }
}

// **Place Cruiser on the Grid**
// Tries to place the Cruiser on the grid starting at a given space and direction.
// Returns true if placement is successful, otherwise false.
bool Cruiser::placeOnGrid(string start_space, char direction, bool print_out) const {
    vector<string> ship_spaces; // Stores the spaces that the Cruiser will occupy.
    try {
        // Try to calculate the required grid spaces for the Cruiser.
        ship_spaces = Grid::getVector(start_space, direction, 1); // Cruiser has a length of 2 (1 additional space from the start).
    } catch (out_of_range& e) {
        // Handle cases where the placement goes out of the grid's bounds.
        if(print_out)
            cout << "Out of range." << endl;
        return false; // Placement failed.
    }

    // Check if any of the intended spaces conflict with existing ships.
    if(this->onGrid->hasNoGoSpace(ship_spaces)) {
        if(print_out)
            cout << "Ships cannot be touching." << endl;
        return false; // Placement failed.
    }

    // Place the Cruiser's studs on the grid.
    for(size_t i = 0; i < 2; i++) 
        this->onGrid->setOnSpace(ship_spaces[i], this->studs[i]);

    // Mark surrounding spaces as no-go zones to avoid overlapping with other ships.
    vector<string> ship_neighbors = Grid::neighborSpaces(ship_spaces);
    this->onGrid->addNoGoSpaces(ship_spaces);       // Add the Cruiser's spaces to no-go zones.
    this->onGrid->addNoGoSpaces(ship_neighbors);    // Add neighboring spaces to no-go zones.

    return true; // Placement was successful.
}
