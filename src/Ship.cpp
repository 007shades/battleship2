#include "Ship.h"

#include "Enums.h" // Includes enums like ShipType, ShipStatus, PlayerType.
#include "Grid.h"  // For the Grid class used to place ships.

#include <string>  // For managing string data (ship names).
    using std::string;
#include <vector>  // For dynamic collections of `Stud` objects.
    using std::vector;

// ** Private Helper Method **

// Sets the ship's name based on its type.
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

// ** Constructors and Destructor **

// Default constructor.
Ship::Ship() {}

// Constructor initializes the ship with a type.
Ship::Ship(ShipType ship_type) : shipType{ship_type} {
    this->set_ship_name(ship_type); // Sets the ship name based on type.
}

// Constructor initializes the ship with a type and owner.
Ship::Ship(ShipType ship_type, PlayerType of_player) 
    : shipType{ship_type}, ofPlayer{of_player} {
    this->set_ship_name(ship_type);
}

// Constructor initializes the ship with a type and grid.
Ship::Ship(ShipType ship_type, Grid* on_grid) 
    : shipType{ship_type}, onGrid{on_grid} {
    this->set_ship_name(ship_type);
    this->ofPlayer = on_grid->getOfPlayer(); // Sets the owner based on grid.
}

// Destructor clears dynamically allocated memory.
Ship::~Ship() {
    this->onGrid = nullptr; // Nullifies grid pointer.
    for (Stud* &intact_stud : this->intactStuds)
        intact_stud = nullptr;
    for (Stud* &destroyed_stud : this->destroyedStuds)
        destroyed_stud = nullptr;
}

// ** Getters **

// Returns the player type (owner of the ship).
PlayerType Ship::getOfPlayer() const {
    return this->ofPlayer;
}

// Returns the grid the ship is placed on.
Grid* Ship::getOnGrid() const {
    return this->onGrid;
}

// Returns the list of intact studs.
vector<Stud*> Ship::getIntactSutds() const {
    return this->intactStuds;
}

// Returns the list of destroyed studs.
vector<Stud*> Ship::getDestroyedStuds() const {
    return this->destroyedStuds;
}

// Returns the ship type.
ShipType Ship::getShipType() const {
    return this->shipType;
}

// Returns the ship's name.
string Ship::getShipName() const {
    return this->shipName;
}

// Returns the ship's status (AFLOAT or SUNKEN).
ShipStatus Ship::getShipStatus() const {
    return this->status;
}

// Returns whether the ship is placed on the grid.
bool Ship::getIsOnGrid() const {
    return this->isOnGrid;
}

// Returns whether the ship is fully ready.
bool Ship::getIsReady() const {
    return this->isReady;
}

// ** Setters **

// Sets the player type (owner of the ship).
void Ship::setOfPlayer(PlayerType of_player) {
    this->ofPlayer = of_player;
}

// Assigns the grid where the ship is placed.
void Ship::setGrid(Grid* on_grid) {
    this->onGrid = on_grid;
}

// Sets the ship type and updates its name.
void Ship::setShipType(ShipType ship_type) {
    this->shipType = ship_type;
    this->set_ship_name(ship_type); // Updates the ship name.
}

// Updates the ship's status (AFLOAT or SUNKEN).
void Ship::setShipStatus(ShipStatus ship_status) {
    this->status = ship_status;
}

// Updates whether the ship is placed on the grid.
void Ship::setIsOnGrid(bool is_on_grid) {
    this->isOnGrid = is_on_grid;
}

// Updates whether the ship is ready for play.
void Ship::setIsReady(bool is_ready) {
    this->isReady = is_ready;
}

// ** Stud Management **

// Checks if a specific stud is intact.
bool Ship::studIsIntact(Stud* stud) const {
    for (Stud* the_stud : this->intactStuds)
        if (the_stud == stud)
            return true;
    return false;
}

// Checks if the ship is sunk.
bool Ship::wasSunk() const {
    return this->isReady && this->intactStuds.empty();
}

// Destroys a specific stud on the ship.
void Ship::destroyStud(Stud* stud) {
    if (!this->hasStud(stud)) // Check if the ship owns this stud.
        return;
    if (!this->studIsIntact(stud)) // Check if the stud is already destroyed.
        return;

    // Remove stud from intact list and add it to destroyed list.
    for (size_t i = 0; i < this->intactStuds.size(); ++i) {
        if (this->intactStuds[i] == stud) {
            this->intactStuds.erase(this->intactStuds.begin() + i);
            break;
        }
    }
    this->destroyedStuds.push_back(stud);
}
