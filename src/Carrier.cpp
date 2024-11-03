#include "Carrier.h" // Include Carrier header file.
#include "Ship.h" // Include base Ship class.

#include "Enums.h" // Include Enums for enumerated types.
#include "Grid.h" // Include Grid for grid-related operations.
#include "Stud.h" // Include Stud class representing parts of the ship.

#include <string> // Include string class.
    using std::string; // Use string from standard namespace.

#include <array> // Include array class for fixed-size arrays.
    using std::array; // Use array from standard namespace.

#include <stdexcept> // Include for exception handling.
    using std::out_of_range; // Use out_of_range exception from standard namespace.

#include <iostream> // Include for input-output operations.
    using std::cout; // Use cout for console output.
    using std::endl; // Use endl for line breaks.

// Constructor: Initializes a Carrier with ShipType::CARRIER.
Carrier::Carrier() : Ship(ShipType::CARRIER) {}

// Constructor: Initializes a Carrier with a specific PlayerType.
Carrier::Carrier(PlayerType of_player) : Ship(ShipType::CARRIER, of_player) {}

// Constructor: Initializes a Carrier on a specific grid and sets up studs.
Carrier::Carrier(Grid* on_grid) : Ship(ShipType::CARRIER, on_grid) 
{
    this->setStuds(); // Call to set up the studs for the carrier.
}

// Constructor: Initializes a Carrier on a specific grid with placement details.
Carrier::Carrier(Grid* on_grid, string start_space, char direction) : Ship(ShipType::BATTLESHIP, on_grid)
{
    this->setStuds(); // Set up the studs for the carrier.
    this->isReady = this->placeOnGrid(start_space, direction); // Try to place the carrier on the grid.
}

// Destructor: Cleans up dynamically allocated Stud objects.
Carrier::~Carrier() {
    for(size_t i = 0; i < 5; ++i) { // Loop through each stud.
        delete this->studs[i]; // Delete the stud to free memory.
        this->studs[i] = nullptr; // Set pointer to nullptr to avoid dangling pointers.
    }
}

// Getter: Returns the array of studs in the carrier.
array<Stud*, 5> Carrier::getStuds() const {
    return this->studs;
}

// Getter: Returns a specific Stud by name if it exists in the carrier.
Stud* Carrier::getStud(StudName stud_name) const {
    for(Stud* stud : this->studs) // Iterate over the studs.
        if(stud->getStudName() == stud_name) // Check if the stud matches the given name.
            return stud; // Return the found stud.
    return nullptr; // Return nullptr if not found.
}

// Method: Checks if a given Stud pointer is part of the carrier.
bool Carrier::hasStud(Stud* stud) const {
    for(Stud* the_stud : this->studs) // Iterate over the studs.
        if(the_stud == stud) // Check if the stud matches.
            return true; // Return true if found.
    return false; // Return false if not found.
}

// Method: Initializes the studs array with new Stud objects.
void Carrier::setStuds() {
    for(size_t i = 0; i < 5; i++) { // Loop to create each stud.
        this->studs[i] = new Stud(Studs::studNames[i], this->ofPlayer, this); // Create new Stud.
        this->intactStuds.push_back(this->studs[i]); // Add the stud to the intactStuds list.
    }
}

// Method: Attempts to place the carrier on the grid.
bool Carrier::placeOnGrid(string start_space, char direction, bool print_out) const {
    vector<string> ship_spaces; // Vector to hold the spaces occupied by the ship.
    try {
        ship_spaces = Grid::getVector(start_space, direction, 4); // Get the vector of spaces for the carrier.
    } catch (out_of_range& e) { // Catch out_of_range exceptions.
        if(print_out)
            cout << "Out of range." << endl; // Print error message.
        return false; // Return false if placement fails.
    }
    if(this->onGrid->hasNoGoSpace(ship_spaces)) { // Check if any space overlaps with restricted spaces.
        if(print_out)
            cout << "Ships cannot be touching." << endl; // Print warning message.
        return false; // Return false if placement fails.
    }
    // Place each stud on the grid.
    for(size_t i = 0; i < 5; i++)
        this->onGrid->setOnSpace(ship_spaces[i], this->studs[i]); // Set stud on the grid space.
    
    // Add no-go spaces to prevent close placement of other ships.
    vector<string> ship_neighbors = Grid::neighborSpaces(ship_spaces); // Get neighboring spaces.
    this->onGrid->addNoGoSpaces(ship_spaces); // Mark occupied spaces as no-go.
    this->onGrid->addNoGoSpaces(ship_neighbors); // Mark neighboring spaces as no-go.
    return true; // Return true if placement is successful.
}
