#include "Stud.h" // Include Stud header file.

#include "Enums.h" // Include for enumerated types used in the class.
#include "Ship.h" // Include for the Ship class.

#include <cctype> // Include for character manipulation functions (e.g., tolower).

// Method: Sets the type of ship based on the StudName.
void Stud::set_ship_type(StudName stud_name) {
    int stud_int = static_cast<int>(stud_name);
    if (stud_int < 5) { // If stud name corresponds to the first 5 elements, it's a Carrier.
        this->forShip = CARRIER;
        this->label = 'A'; // Label for Carrier.
    }
    else if (stud_int < 9) { // If stud name corresponds to the next 4 elements, it's a Battleship.
        this->forShip = BATTLESHIP;
        this->label = 'B'; // Label for Battleship.
    }
    else if (stud_int < 12) { // If stud name corresponds to the next 3 elements, it's a Destroyer.
        this->forShip = DESTROYER;
        this->label = 'D'; // Label for Destroyer.
    }
    else if (stud_int < 15) { // If stud name corresponds to the next 3 elements, it's a Submarine.
        this->forShip = SUBMARINE;
        this->label = 'S'; // Label for Submarine.
    }
    else { // Otherwise, it's a Cruiser.
        this->forShip = CRUISER;
        this->label = 'C'; // Label for Cruiser.
    }
}

// Default constructor.
Stud::Stud() {}

// Constructor: Initializes a Stud with a StudName.
Stud::Stud(StudName stud_name) : studName{stud_name} {
    set_ship_type(stud_name); // Set the type of ship and label.
}

// Constructor: Initializes a Stud with a StudName and a GridSpace.
Stud::Stud(StudName stud_name, GridSpace* grid_space) : studName{stud_name}, gridspace{grid_space} {
    set_ship_type(stud_name); // Set the type of ship and label.
    this->onSpace = grid_space->getSpaceName(); // Set the space the stud is on.
    this->ofPlayer = grid_space->getOfPlayer(); // Set the player type owning the stud.
}

// Constructor: Initializes a Stud with a StudName and PlayerType.
Stud::Stud(StudName stud_name, PlayerType of_player) : studName{stud_name}, ofPlayer{of_player} {
    set_ship_type(stud_name); // Set the type of ship and label.
}

// Constructor: Initializes a Stud with a StudName, GridSpace, and StudStatus.
Stud::Stud(StudName stud_name, GridSpace* grid_space, StudStatus the_status) : gridspace{grid_space}, status{the_status} {
    set_ship_type(stud_name); // Set the type of ship and label.
    this->onSpace = grid_space->getSpaceName(); // Set the space the stud is on.
    this->ofPlayer = grid_space->getOfPlayer(); // Set the player type owning the stud.
}

// Constructor: Initializes a Stud with a StudName, PlayerType, and StudStatus.
Stud::Stud(StudName stud_name, PlayerType of_player, StudStatus the_status) : studName{stud_name}, ofPlayer{of_player}, status{the_status} {
    set_ship_type(stud_name); // Set the type of ship and label.
}

// Constructor: Initializes a Stud with a StudName, PlayerType, and a pointer to a Ship.
Stud::Stud(StudName stud_name, PlayerType of_player, Ship* of_ship) : studName{stud_name}, ofPlayer{of_player}, ofShip{of_ship} {
    set_ship_type(stud_name); // Set the type of ship and label.
}

// Destructor: Cleans up resources used by the Stud.
Stud::~Stud() {
    this->gridspace = nullptr; // Set gridspace pointer to nullptr.
    this->ofShip = nullptr; // Set ofShip pointer to nullptr.
}

// Getter: Returns the StudName.
StudName Stud::getStudName() const {
    return this->studName;
}

// Getter: Returns the space the stud is on.
SpaceName Stud::getOnSpace() const {
    return this->onSpace;
}

// Getter: Returns the type of ship the stud belongs to.
ShipType Stud::getForShip() const {
    return this->forShip;
}

// Getter: Returns the PlayerType that owns the stud.
PlayerType Stud::getOfPlayer() const {
    return this->ofPlayer;
}

// Getter: Returns the status of the stud (INTACT or COMPROMISED).
StudStatus Stud::getStatus() const {
    return this->status;
}

// Getter: Returns a pointer to the Ship the stud is part of.
Ship* Stud::getOfShip() const {
    return this->ofShip;
}

// Getter: Returns the label of the stud.
char Stud::getLabel() const {
    return this->label;
}

// Setter: Sets the StudName and updates the type of ship and label.
void Stud::setStudName(StudName stud_name) {
    this->studName = stud_name;
    this->set_ship_type(stud_name); // Update the ship type and label.
}

// Setter: Sets the space the stud is on.
void Stud::setOnSpace(SpaceName on_space) {
    this->onSpace = on_space;
}

// Setter: Sets the PlayerType that owns the stud.
void Stud::setOfPlayer(PlayerType of_player) {
    this->ofPlayer = of_player;
}

// Setter: Sets the status of the stud.
void Stud::setStatus(StudStatus the_status) { 
    this->status = the_status;
}

// Setter: Sets the Ship the stud is part of.
void Stud::setOfShip(Ship* of_ship) {
    this->ofShip = of_ship;
}

// Setter: Sets the label of the stud.
void Stud::setLabel(char stud_label) {
    this->label = stud_label;
}

// Method: Checks if the stud was hit.
bool Stud::wasHit() const {
    return this->status == COMPROMISED;
}

// Method: Marks the stud as hit and updates its label and ship status.
void Stud::hit() {
    this->status = COMPROMISED; // Update the status to COMPROMISED.
    this->label = static_cast<char>(tolower(static_cast<unsigned char>(this->label))); // Convert label to lowercase.
    if(this->ofShip != nullptr)
        this->ofShip->destroyStud(this); // Notify the ship that the stud was hit.
}
