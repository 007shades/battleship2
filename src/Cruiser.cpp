#include "Cruiser.h" // Include Cruiser header file.
#include "Ship.h" // Include base class Ship header file.

#include "Enums.h" // Include Enums for predefined enumerations.
#include "Grid.h" // Include Grid class for handling game grid.
#include "Stud.h" // Include Stud class for ship parts.

#include <string> // Include string for handling text.
    using std::string; // Use string from the standard namespace.

#include <array> // Include array for fixed-size arrays.
    using std::array; // Use array from the standard namespace.

#include <stdexcept> // Include for handling exceptions like out_of_range.
    using std::out_of_range; // Use out_of_range from the standard namespace.

#include <iostream> // Include for input-output operations.
    using std::cout; // Use cout for console output.
    using std::endl; // Use endl for line breaks.

// Default constructor: Initializes a Cruiser with ShipType::CRUISER.
Cruiser::Cruiser() : Ship(ShipType::CRUISER) {}

// Constructor: Initializes a Cruiser with a specific player type.
Cruiser::Cruiser(PlayerType of_player) : Ship(ShipType::CRUISER, of_player) {}

// Constructor: Initializes a Cruiser with a grid and sets up studs.
Cruiser::Cruiser(Grid* on_grid) : Ship(ShipType::CRUISER, on_grid) 
{
    this->setStuds(); // Set up studs for the cruiser.
}

// Constructor: Initializes a Cruiser, sets up studs, and attempts to place it on the grid.
Cruiser::Cruiser(Grid* on_grid, string start_space, char direction) : Ship(ShipType::BATTLESHIP, on_grid) 
{
// NOTE: Change ShipType::BATTLESHIP to ShipType::CRUISER to correctly represent the Cruiser type. (line 34)
    this->setStuds(); // Set up studs for the cruiser.
    this->isReady = this->placeOnGrid(start_space, direction); // Try placing the cruiser on the grid.
}

// Destructor: Cleans up dynamically allocated Stud objects.
Cruiser::~Cruiser() {
    for(size_t i = 0; i < 2; ++i) {
        delete this->studs[i]; // Delete each stud to free memory.
        this->studs[i] = nullptr; // Set pointer to nullptr to prevent dangling pointers.
    }
}

// Getter: Returns the array of studs in the cruiser.
array<Stud*, 2> Cruiser::getStuds() const {
    return this->studs;
}

// Getter: Returns a specific Stud by name if it exists in the cruiser.
Stud* Cruiser::getStud(StudName stud_name) const {
    for(Stud* stud : this->studs) // Iterate over the studs.
        if(stud->getStudName() == stud_name) // Check if the stud matches the name.
            return stud; // Return the found stud.
    return nullptr; // Return nullptr if not found.
}

// Method: Checks if the given Stud pointer is part of the cruiser.
bool Cruiser::hasStud(Stud* stud) const {
    for(Stud* the_stud : this->studs) // Iterate over the studs.
        if(the_stud == stud) // Check if the pointer matches.
            return true; // Return true if found.
    return false; // Return false if not found.
}

// Method: Initializes the studs array with new Stud objects.
void Cruiser::setStuds() {
    for(size_t i = 15, j = 0; i < 17; i++, j++) {
        this->studs[j] = new Stud(Studs::studNames[i], this->ofPlayer, this); // Create new Stud.
        this->intactStuds.push_back(this->studs[j]); // Add to intact studs list.
    }
}

// Method: Attempts to place the cruiser on the grid.
bool Cruiser::placeOnGrid(string start_space, char direction, bool print_out) const {
    vector<string> ship_spaces; // Vector to hold the spaces occupied by the ship.
    try {
        ship_spaces = Grid::getVector(start_space, direction, 1); // Get vector of spaces.
    } catch (out_of_range& e) { // Catch out_of_range exceptions.
        if(print_out)
            cout << "Out of range." << endl; // Print error message.
        return false; // Return false if placement failed.
    }
    if(this->onGrid->hasNoGoSpace(ship_spaces)) { // Check if any space is restricted.
        if(print_out)
            cout << "Ships cannot be touching." << endl; // Print warning message.
        return false; // Return false if placement failed.
    }
    // Place each stud on the grid.
    for(size_t i = 0; i < 2; i++)
        this->onGrid->setOnSpace(ship_spaces[i], this->studs[i]);
    
    // Add no-go spaces to prevent close placement of other ships.
    vector<string> ship_neighbors = Grid::neighborSpaces(ship_spaces); // Get neighboring spaces.
    this->onGrid->addNoGoSpaces(ship_spaces); // Mark occupied spaces as no-go.
    this->onGrid->addNoGoSpaces(ship_neighbors); // Mark neighboring spaces as no-go.
    
    return true; // Return true if placement was successful.
}
