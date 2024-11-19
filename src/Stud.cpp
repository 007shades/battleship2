#include "Stud.h"
#include "Enums.h"    // For enumerations like StudName, PlayerType, etc.
#include "Ship.h"     // Forward declaration resolved here.

#include <cctype>     // For `tolower` function used in the `hit` method.

// ** Private Helper Method **
// Sets the ship type and label based on the stud name.
void Stud::set_ship_type(StudName stud_name) {
    int stud_int = static_cast<int>(stud_name); // Convert StudName enum to integer.

    // Determine the ship type and label based on the range of stud name.
    if (stud_int < 5) {
        this->forShip = CARRIER;
        this->label = 'A'; // 'A' for Carrier.
    } else if (stud_int < 9) {
        this->forShip = BATTLESHIP;
        this->label = 'B'; // 'B' for Battleship.
    } else if (stud_int < 12) {
        this->forShip = DESTROYER;
        this->label = 'D'; // 'D' for Destroyer.
    } else if (stud_int < 15) {
        this->forShip = SUBMARINE;
        this->label = 'S'; // 'S' for Submarine.
    } else {
        this->forShip = CRUISER;
        this->label = 'C'; // 'C' for Cruiser.
    }
}

// ** Constructors and Destructor **

// Default constructor.
Stud::Stud() {}

// Constructor initializes the stud with its name.
Stud::Stud(StudName stud_name) : studName{stud_name} {
    set_ship_type(stud_name); // Sets the ship type and label.
}

// Constructor initializes the stud with its name and grid space.
Stud::Stud(StudName stud_name, GridSpace* grid_space)
    : studName{stud_name}, gridspace{grid_space} {
    set_ship_type(stud_name);
    this->onSpace = grid_space->getSpaceName(); // Set the space name.
    this->ofPlayer = grid_space->getOfPlayer(); // Set the owner.
}

// Constructor initializes the stud with its name and owner.
Stud::Stud(StudName stud_name, PlayerType of_player)
    : studName{stud_name}, ofPlayer{of_player} {
    set_ship_type(stud_name);
}

// Constructor initializes the stud with its name, grid space, and status.
Stud::Stud(StudName stud_name, GridSpace* grid_space, StudStatus the_status)
    : gridspace{grid_space}, status{the_status} {
    set_ship_type(stud_name);
    this->onSpace = grid_space->getSpaceName();
    this->ofPlayer = grid_space->getOfPlayer();
}

// Constructor initializes the stud with its name, owner, and status.
Stud::Stud(StudName stud_name, PlayerType of_player, StudStatus the_status)
    : studName{stud_name}, ofPlayer{of_player}, status{the_status} {
    set_ship_type(stud_name);
}

// Constructor initializes the stud with its name, owner, and associated ship.
Stud::Stud(StudName stud_name, PlayerType of_player, Ship* of_ship)
    : studName{stud_name}, ofPlayer{of_player}, ofShip{of_ship} {
    set_ship_type(stud_name);
}

// Destructor clears pointers to prevent memory leaks.
Stud::~Stud() {
    this->gridspace = nullptr;
    this->ofShip = nullptr;
}

// ** Getters **

// Returns the stud's name.
StudName Stud::getStudName() const {
    return this->studName;
}

// Returns the grid space the stud is on.
SpaceName Stud::getOnSpace() const {
    return this->onSpace;
}

// Returns the ship type associated with the stud.
ShipType Stud::getForShip() const {
    return this->forShip;
}

// Returns the player type (owner) of the stud.
PlayerType Stud::getOfPlayer() const {
    return this->ofPlayer;
}

// Returns the stud's status (INTACT or COMPROMISED).
StudStatus Stud::getStatus() const {
    return this->status;
}

// Returns the ship to which the stud belongs.
Ship* Stud::getOfShip() const {
    return this->ofShip;
}

// Returns the label representing the stud.
char Stud::getLabel() const {
    return this->label;
}

// ** Setters **

// Sets the stud's name and updates its ship type and label.
void Stud::setStudName(StudName stud_name) {
    this->studName = stud_name;
    this->set_ship_type(stud_name);
}

// Sets the grid space the stud is on.
void Stud::setOnSpace(SpaceName on_space) {
    this->onSpace = on_space;
}

// Sets the player type (owner) of the stud.
void Stud::setOfPlayer(PlayerType of_player) {
    this->ofPlayer = of_player;
}

// Updates the stud's status.
void Stud::setStatus(StudStatus the_status) {
    this->status = the_status;
}

// Links the stud to a specific ship.
void Stud::setOfShip(Ship* of_ship) {
    this->ofShip = of_ship;
}

// Updates the stud's label.
void Stud::setLabel(char stud_label) {
    this->label = stud_label;
}

// ** Status and Interaction **

// Checks if the stud has been hit.
bool Stud::wasHit() const {
    return this->status == COMPROMISED;
}

// Marks the stud as hit, updates its label, and notifies the ship.
void Stud::hit() {
    this->status = COMPROMISED; // Update status.
    this->label = static_cast<char>(tolower(static_cast<unsigned char>(this->label))); // Lowercase label.
    if (this->ofShip != nullptr) {
        this->ofShip->destroyStud(this); // Notify the associated ship of the hit.
    }
}
