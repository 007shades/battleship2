#include "Ship.h" // Include Ship header file.

#include "Enums.h" // Include for enumerated types used in the class.
#include "Grid.h" // Include for the Grid class.

#include <string> // Include for handling strings.
    using std::string; // Use string from the standard namespace.

#include <vector> // Include for using vector class.
    using std::vector; // Use vector from the standard namespace.

// Method: Sets the name of the ship based on its type.
void Ship::set_ship_name(ShipType ship_type) {
    switch (ship_type) {
        case CARRIER: {
            this->shipName = "Carrier";
            break;
        }
        case BATTLESHIP: {
            this->shipName = "Battleship";
            break;
        }
        case DESTROYER: {
            this->shipName = "Destroyer";
            break;
        }
        case SUBMARINE: {
            this->shipName = "Submarine";
            break;
        }
        case CRUISER: {
            this->shipName = "Cruiser";
            break;
        }
    }
}

// Default constructor.
Ship::Ship() {}

// Constructor: Initializes a Ship with a specific ShipType.
Ship::Ship(ShipType ship_type) : shipType{ship_type} {
    this->set_ship_name(ship_type); // Set the name of the ship.
}

// Constructor: Initializes a Ship with a ShipType and player type.
Ship::Ship(ShipType ship_type, PlayerType of_player) : shipType{ship_type}, ofPlayer{of_player} {
    this->set_ship_name(ship_type); // Set the name of the ship.
}

// Constructor: Initializes a Ship with a ShipType and places it on a grid.
Ship::Ship(ShipType ship_type, Grid* on_grid) : shipType{ship_type}, onGrid{on_grid} {
    this->set_ship_name(ship_type); // Set the name of the ship.
    this->ofPlayer = on_grid->getOfPlayer(); // Set the player type based on the grid.
}

// Destructor: Cleans up resources used by the Ship.
Ship::~Ship() {
    this->onGrid = nullptr; // Set grid pointer to nullptr.
    for(Stud* &intact_stud : this->intactStuds)
        intact_stud = nullptr; // Set intact studs to nullptr.
    for(Stud* &destroyed_stud : this->destroyedStuds)
        destroyed_stud = nullptr; // Set destroyed studs to nullptr.
}

// Getter: Returns the PlayerType associated with the ship.
PlayerType Ship::getOfPlayer() const {
    return this->ofPlayer;
}

// Getter: Returns the grid the ship is on.
Grid* Ship::getOnGrid() const {
    return this->onGrid;
}

// Getter: Returns a vector of intact studs on the ship.
vector<Stud*> Ship::getIntactSutds() const {
    return this->intactStuds;
}

// Getter: Returns a vector of destroyed studs on the ship.
vector<Stud*> Ship::getDestroyedStuds() const {
    return this->destroyedStuds;
}

// Getter: Returns the type of the ship.
ShipType Ship::getShipType() const {
    return this->shipType;
}

// Getter: Returns the name of the ship.
string Ship::getShipName() const {
    return this->shipName;
}

// Getter: Returns the status of the ship (AFLOAT or SUNKEN).
ShipStatus Ship::getShipStatus() const {
    return this->status;
}

// Getter: Returns whether the ship is placed on the grid.
bool Ship::getIsOnGrid() const {
    return this->isOnGrid;
}

// Getter: Returns whether the ship is ready (placed and valid).
bool Ship::getIsReady() const {
    return this->isReady;
}

// Setter: Sets the PlayerType associated with the ship.
void Ship::setOfPlayer(PlayerType of_player) {
    this->ofPlayer = of_player;
}

// Setter: Sets the grid the ship is on.
void Ship::setGrid(Grid* on_grid) {
    this->onGrid = on_grid;
}

// Setter: Sets the type of the ship and updates the name.
void Ship::setShipType(ShipType ship_type) {
    this->shipType = ship_type;
    this->set_ship_name(ship_type); // Update the ship name.
}

// Setter: Sets the status of the ship.
void Ship::setShipStatus(ShipStatus ship_status) {
    this->status = ship_status;
}

// Setter: Sets whether the ship is on the grid.
void Ship::setIsOnGrid(bool is_on_grid) {
    this->isOnGrid = is_on_grid;
}

// Setter: Sets whether the ship is ready (placed and valid).
void Ship::setIsReady(bool is_ready) {
    this->isReady = is_ready;
}

// Method: Checks if a specific stud on the ship is intact.
bool Ship::studIsIntact(Stud* stud) const {
    for(Stud* the_stud : this->intactStuds)
        if (the_stud == stud)
            return true;
    return false;
}

// Method: Checks if the ship has been sunk (all studs destroyed).
bool Ship::wasSunk() const {
    return this->isReady && !this->intactStuds.size(); // Return true if no intact studs remain.
}

// Method: Marks a stud as destroyed and updates the ship's status.
void Ship::destroyStud(Stud* stud) {
    if(!this->hasStud(stud))
        return; // Return if the ship doesn't have this stud.
    if(!this->studIsIntact(stud))
        return; // Return if the stud is already destroyed.
    for(size_t i = 0; i < this->intactStuds.size(); ++i) {
        if(this->intactStuds[i] == stud) {
            this->intactStuds.erase(this->intactStuds.begin() + i); // Remove stud from intact list.
            break;
        }
    }
    this->destroyedStuds.push_back(stud); // Add the stud to the destroyed list.
}
