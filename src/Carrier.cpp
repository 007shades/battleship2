#include "Carrier.h"
#include "Ship.h"

#include "Enums.h"     // For ShipType and PlayerType enumerations.
#include "Grid.h"      // For placing the Carrier on the grid.
#include "Stud.h"      // For managing the Carrier's studs.

#include <string>
    using std::string; // For space and ship names.
#include <array>
    using std::array;  // To manage fixed-size arrays for studs.
#include <stdexcept>
    using std::out_of_range; // For exception handling during grid operations.
#include <iostream>
    using std::cout;
    using std::endl;

// **Default Constructor**
// Initializes a Carrier without any player or grid assignment.
Carrier::Carrier() : Ship(ShipType::CARRIER) {}

// **Player-Specific Constructor**
// Initializes a Carrier for a specific player.
Carrier::Carrier(PlayerType of_player) : Ship(ShipType::CARRIER, of_player) {}

// **Grid-Specific Constructor**
// Initializes a Carrier and associates it with a grid.
Carrier::Carrier(Grid* on_grid) : Ship(ShipType::CARRIER, on_grid) 
{
    this->setStuds(); // Sets up the studs associated with the Carrier.
}

// **Full Constructor**
// Initializes a Carrier, sets its studs, and attempts to place it on the grid.
Carrier::Carrier(Grid* on_grid, string start_space, char direction) : Ship(ShipType::CARRIER, on_grid)
{
    this->setStuds(); // Sets up the studs.
    this->isReady = this->placeOnGrid(start_space, direction); // Attempts to place the Carrier on the grid.
}

// **Destructor**
// Cleans up dynamically allocated memory for the studs.
Carrier::~Carrier() {
    for(size_t i = 0; i < 5; ++i) {
        delete this->studs[i]; // Deallocate each stud.
        this->studs[i] = nullptr; // Set the pointer to nullptr.
    }
} 

// **Getter for All Studs**
// Returns the array of pointers to the Carrier's studs.
array<Stud*, 5> Carrier::getStuds() const {
    return this->studs;
}

// **Getter for a Specific Stud**
// Returns a pointer to a specific stud based on its name.
Stud* Carrier::getStud(StudName stud_name) const {
    for(Stud* stud : this->studs)
        if(stud->getStudName() == stud_name) // Match the stud by its name.
            return stud;
    return nullptr; // Return nullptr if no match is found.
}

// **Check if a Stud Belongs to the Carrier**
// Determines whether the given stud is part of this Carrier.
bool Carrier::hasStud(Stud* stud) const {
    for(Stud* the_stud : this->studs)
        if(the_stud == stud) // Compare pointers to identify the stud.
            return true;
    return false; // Return false if the stud is not part of the Carrier.
}

// **Set Up Studs**
// Initializes the Carrier's studs and associates them with the player and the ship.
void Carrier::setStuds() {
    for(size_t i = 0; i < 5; i++) {
        this->studs[i] = new Stud(Studs::studNames[i], this->ofPlayer, this); // Dynamically allocate new studs.
        this->intactStuds.push_back(this->studs[i]); // Add the stud to the intact list.
    }
}

// **Place Carrier on the Grid**
// Tries to place the Carrier on the grid starting from a specific space and direction.
// Returns true if placement is successful, otherwise false.
bool Carrier::placeOnGrid(string start_space, char direction, bool print_out) const {
    vector<string> ship_spaces;
    try {
        // Attempt to get a vector of grid spaces for the Carrier.
        ship_spaces = Grid::getVector(start_space, direction, 4); // Carrier has a length of 5 (4 additional spaces from the start).
    } catch (out_of_range& e) {
        // Handle out-of-bound placement attempts.
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

    // Place the Carrier's studs on the grid.
    for(size_t i = 0; i < 5; i++)
        this->onGrid->setOnSpace(ship_spaces[i], this->studs[i]);

    // Mark surrounding spaces as no-go zones.
    vector<string> ship_neighbors = Grid::neighborSpaces(ship_spaces);
    this->onGrid->addNoGoSpaces(ship_spaces);       // Add the Carrier's spaces to no-go zones.
    this->onGrid->addNoGoSpaces(ship_neighbors);    // Add neighboring spaces to no-go zones.

    return true; // Placement successful.
}
