#include "Submarine.h"
#include "Ship.h"

#include "Enums.h"
#include "Grid.h"
#include "Stud.h"

#include <string>
    using std::string;

#include <array>
    using std::array;

#include <stdexcept>
    using std::out_of_range;

#include <iostream>
    using std::cout;
    using std::endl;

// **Default Constructor**
// Creates a Submarine object without initializing it on a grid or associating it with a player.
Submarine::Submarine() : Ship(ShipType::SUBMARINE) {}

// **Parameterized Constructor**
// Associates the Submarine with a specific player type.
Submarine::Submarine(PlayerType of_player) : Ship(ShipType::SUBMARINE, of_player) {}

// **Grid Constructor**
// Places the Submarine on a grid and initializes its studs (individual ship segments).
Submarine::Submarine(Grid* on_grid) : Ship(ShipType::SUBMARINE, on_grid) 
{
    this->setStuds(); // Initializes the studs that represent parts of the Submarine.
}

// **Full Constructor**
// Places the Submarine on a grid at a specific location and orientation.
// It also initializes the studs and checks if the ship placement is valid.
Submarine::Submarine(Grid* on_grid, string start_space, char direction) : Ship (ShipType::SUBMARINE, on_grid)
{
    this->setStuds(); // Initializes the studs.
    this->isReady = this->placeOnGrid(start_space, direction); // Places the ship on the grid.
}

// **Destructor**
// Cleans up dynamically allocated memory for the studs of the Submarine.
Submarine::~Submarine() {
    for(size_t i = 0; i < 3; ++i) { // Submarines have 3 studs.
        delete this->studs[i]; // Deletes each stud.
        this->studs[i] = nullptr; // Sets the pointer to null to prevent dangling references.
    }
} 

// **Getters**
// Returns an array of pointers to the studs that make up the Submarine.
array<Stud*, 3> Submarine::getStuds() const {
    return this->studs;
}

// Returns a pointer to a specific stud by its name.
Stud* Submarine::getStud(StudName stud_name) const {
    for(Stud* stud : this->studs) // Loops through all the studs.
        if(stud->getStudName() == stud_name) // Matches the stud by name.
            return stud;
    return nullptr; // Returns nullptr if no match is found.
}

// **Check if the Submarine has a specific stud**
bool Submarine::hasStud(Stud* stud) const {
    for(Stud* the_stud : this->studs) // Loops through all the studs.
        if(the_stud == stud) // Checks if the given stud matches.
            return true;
    return false; // Returns false if the stud is not found.
}

// **Initialize Studs**
// Sets up the 3 studs for the Submarine, assigns names, and links them to the Submarine.
void Submarine::setStuds() {
    for(size_t i=12, j=0; i<15; i++, j++) { // Submarine's studs are indexed 12-14.
        this->studs[j] = new Stud(Studs::studNames[i], this->ofPlayer, this); // Creates a new stud.
        this->intactStuds.push_back(this->studs[j]); // Adds the stud to the intact studs list.
    }
}

// **Place Submarine on Grid**
// Places the Submarine on the grid, ensuring the placement is valid and doesn't conflict with other ships.
bool Submarine::placeOnGrid(string start_space, char direction, bool print_out) const {
    vector<string> ship_spaces; // List of spaces the ship will occupy.

    try {
        // Calculates the spaces based on the starting point and direction.
        ship_spaces = Grid::getVector(start_space, direction, 2); // Submarine occupies 3 spaces.
    } catch (out_of_range& e) {
        if(print_out)
            cout << "Out of range." << endl; // Prints an error if placement is out of bounds.
        return false;
    }

    // Checks if the calculated spaces are invalid (e.g., overlap or adjacent to other ships).
    if(this->onGrid->hasNoGoSpace(ship_spaces)) {
        if(print_out)
            cout << "Ships cannot be touching." << endl; // Prints an error if the placement is invalid.
        return false;
    }

    // Places each stud of the Submarine on the corresponding grid spaces.
    for(size_t i = 0; i < 3; i++)
        this->onGrid->setOnSpace(ship_spaces[i], this->studs[i]);

    // Adds neighboring spaces to the "no-go" list to prevent other ships from being placed too close.
    vector<string> ship_neighbors = Grid::neighborSpaces(ship_spaces);
    this->onGrid->addNoGoSpaces(ship_spaces); // Marks the ship's spaces as occupied.
    this->onGrid->addNoGoSpaces(ship_neighbors); // Marks the neighboring spaces as restricted.

    return true; // Returns true if the placement is successful.
}
