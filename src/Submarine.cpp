#include "Submarine.h" // Include Submarine header file.
#include "Ship.h" // Include Ship base class header file.

#include "Enums.h" // Include for enumerated types used in the class.
#include "Grid.h" // Include for the Grid class.
#include "Stud.h" // Include for the Stud class.

#include <string> // Include for using string.
    using std::string; // Use string from the standard namespace.

#include <array> // Include for using array.
    using std::array; // Use array from the standard namespace.

#include <stdexcept> // Include for handling exceptions.
    using std::out_of_range; // Use out_of_range from the standard namespace.

#include <iostream> // Include for console input/output.
    using std::cout; // Use cout for output.
    using std::endl; // Use endl for newline.

// Constructor: Initializes a Submarine without parameters.
Submarine::Submarine() : Ship(ShipType::SUBMARINE) {}

// Constructor: Initializes a Submarine with a PlayerType.
Submarine::Submarine(PlayerType of_player) : Ship(ShipType::SUBMARINE, of_player) {}

// Constructor: Initializes a Submarine with a Grid.
Submarine::Submarine(Grid* on_grid) : Ship(ShipType::SUBMARINE, on_grid) {
    this->setStuds(); // Set the studs for the Submarine.
}

// Constructor: Initializes a Submarine with a Grid, start space, and direction.
// Note: The ShipType was mistakenly set to BATTLESHIP; changed to SUBMARINE to match the class.
Submarine::Submarine(Grid* on_grid, string start_space, char direction) : Ship(ShipType::SUBMARINE, on_grid) {
    this->setStuds(); // Set the studs for the Submarine.
    this->isReady = this->placeOnGrid(start_space, direction); // Place the Submarine on the grid.
}

// Destructor: Cleans up resources used by the Submarine.
Submarine::~Submarine() {
    for(size_t i = 0; i < 3; ++i) {
        delete this->studs[i]; // Delete each stud.
        this->studs[i] = nullptr; // Set stud pointer to nullptr.
    }
}

// Method: Returns an array of pointers to the studs of the Submarine.
array<Stud*, 3> Submarine::getStuds() const {
    return this->studs;
}

// Method: Returns a pointer to a stud given its StudName.
Stud* Submarine::getStud(StudName stud_name) const {
    for(Stud* stud : this->studs)
        if(stud->getStudName() == stud_name)
            return stud;
    return nullptr; // Return nullptr if the stud is not found.
}

// Method: Checks if the Submarine has a specific stud.
bool Submarine::hasStud(Stud* stud) const {
    for(Stud* the_stud : this->studs)
        if(the_stud == stud)
            return true;
    return false;
}

// Method: Sets the studs for the Submarine and adds them to the list of intact studs.
void Submarine::setStuds() {
    for(size_t i = 12, j = 0; i < 15; i++, j++) {
        this->studs[j] = new Stud(Studs::studNames[i], this->ofPlayer, this); // Create a new stud.
        this->intactStuds.push_back(this->studs[j]); // Add to the intact studs vector.
    }
}

// Method: Places the Submarine on the grid based on a start space and direction.
bool Submarine::placeOnGrid(string start_space, char direction, bool print_out) const {
    vector<string> ship_spaces; // Vector to hold spaces occupied by the Submarine.
    try {
        ship_spaces = Grid::getVector(start_space, direction, 2); // Get vector of grid spaces for the Submarine.
    } catch (out_of_range& e) {
        if(print_out)
            cout << "Out of range." << endl; // Print message if the placement is out of range.
        return false;
    }
    if(this->onGrid->hasNoGoSpace(ship_spaces)) { // Check if the placement is valid.
        if(print_out)
            cout << "Ships cannot be touching." << endl; // Print message if spaces are invalid.
        return false;
    }
    // Place each stud on the respective grid space.
    for(size_t i = 0; i < 3; i++)
        this->onGrid->setOnSpace(ship_spaces[i], this->studs[i]);
    
    vector<string> ship_neighbors = Grid::neighborSpaces(ship_spaces); // Get neighboring spaces.
    this->onGrid->addNoGoSpaces(ship_spaces); // Add occupied spaces to the no-go list.
    this->onGrid->addNoGoSpaces(ship_neighbors); // Add neighboring spaces to the no-go list.
    return true; // Return true if placement is successful.
}
