#include "GridSpace.h"  // Includes the GridSpace class header file.

#include "Enums.h"      // Includes game-related enumerations.
#include "Stud.h"       // Includes the Stud class for ship components.

#include <string>       // Provides the string class.
    using std::string;

#include <stdexcept>    // Provides standard exceptions like out_of_range and invalid_argument.
    using std::out_of_range;
    using std::invalid_argument;

// ** PRIVATE HELPER METHODS **

// Sets up the data for a space using its SpaceName.
void GridSpace::set_space_data(SpaceName space_name) {
    string space_string = Spaces::stringFromName(space_name); // Convert SpaceName to string.
    char letter = space_string.at(0);                        // Extract the column letter.
    char number = space_string.length() == 3 ? '0' : space_string.at(1); // Extract the row number.
    this->spaceString = space_string;
    this->letter = letter;
    this->number = number;
    this->column = Spaces::columnFromChar(letter); // Convert column letter to Column enum.
    this->row = Spaces::rowFromChar(number);       // Convert row number to Row enum.
}

// ** CONSTRUCTORS AND DESTRUCTOR **

// Default constructor.
GridSpace::GridSpace() {}

// Constructor initializes space with a SpaceName.
GridSpace::GridSpace(SpaceName space_name) : spaceName{space_name} {
    this->set_space_data(space_name); // Set up space data.
}

// Constructor initializes space with a SpaceName and player type.
GridSpace::GridSpace(SpaceName space_name, PlayerType of_player) 
    : spaceName{space_name}, ofPlayer{of_player} {
    this->set_space_data(space_name); // Set up space data.
}

// Constructor initializes space with a SpaceName, player type, and space status.
GridSpace::GridSpace(SpaceName space_name, PlayerType of_player, SpaceStatus space_status) 
    : spaceName{space_name}, ofPlayer{of_player}, status{space_status} {
    this->set_space_data(space_name); // Set up space data.
}

// Constructor initializes space with a SpaceName, player type, status, and a Stud.
GridSpace::GridSpace(SpaceName space_name, PlayerType of_player, SpaceStatus space_status, Stud* the_stud) 
    : spaceName{space_name}, ofPlayer{of_player}, status{space_status}, stud{the_stud} {
    this->set_space_data(space_name); // Set up space data.
}

// Destructor ensures no dangling Stud pointer.
GridSpace::~GridSpace() {
    this->stud = nullptr; // Clears the stud pointer.
}

// ** GETTERS **

// Returns the SpaceName of the space.
SpaceName GridSpace::getSpaceName() const {
    return this->spaceName;
}

// Returns the Column enum of the space.
Column GridSpace::getColumn() const {
    return this->column;
}

// Returns the Row enum of the space.
Row GridSpace::getRow() const {
    return this->row;
}

// Returns the PlayerType associated with the space.
PlayerType GridSpace::getOfPlayer() const {
    return this->ofPlayer;
}

// Returns the SpaceStatus of the space.
SpaceStatus GridSpace::getStatus() const {
    return this->status;
}

// Returns the Stud pointer on the space.
Stud* GridSpace::getStud() const {
    return this->stud;
}

// Returns the string representation of the space.
string GridSpace::getSpaceString() const {
    return this->spaceString;
}

// Returns the column letter of the space.
char GridSpace::getLetter() const {
    return this->letter;
}

// Returns the row number of the space.
char GridSpace::getNumber() const {
    return this->number;
}

// Returns the label of the space.
char GridSpace::getLabel() const {
    return this->label;
}

// Returns the prime label of the space.
char GridSpace::getPrimeLabel() const {
    return this->primeLabel;
}

// ** SETTERS **

// Sets the SpaceName and updates associated data.
void GridSpace::setSpaceName(SpaceName space_name) {
    this->spaceName = space_name;
    this->set_space_data(space_name);
}

// Sets the player associated with the space.
void GridSpace::setOfPlayer(PlayerType of_player) {
    this->ofPlayer = of_player;
}

// Sets the status of the space.
void GridSpace::setStatus(SpaceStatus space_status) {
    this->status = space_status;
}

// Sets the Stud on the space.
void GridSpace::setStud(Stud* the_stud) {
    this->stud = the_stud;
}

// Sets the label of the space.
void GridSpace::setLabel(char label) {
    this->label = label;
}

// Adds a Stud to the space, throwing an error if already occupied.
void GridSpace::addStud(Stud* the_stud) {
    if (this->hasStud())
        throw invalid_argument("Space already occupied.");
    this->stud = the_stud;
    if (this->ofPlayer == MAN)
        this->label = the_stud->getLabel();
    this->primeLabel = the_stud->getLabel();
}

// ** STATUS CHECKS **

// Checks if the space has a Stud.
bool GridSpace::hasStud() const {
    return this->stud != nullptr;
}

// Checks if the space has already been targeted.
bool GridSpace::wasTargeted() const {
    return this->status == SpaceStatus::TARGETED;
}

// ** LABEL MODIFICATION **

// Updates the label and prime label based on status and player.
void GridSpace::modifyLabel() {
    if (this->ofPlayer == PlayerType::CPU) {
        this->label = this->hasStud() ? 'H' : 'M'; // 'H' for hit, 'M' for miss.
        this->primeLabel = this->hasStud() ? this->stud->getLabel() : '@'; // '@' for unknown.
    } else {
        this->label = this->hasStud() ? this->stud->getLabel() : '@';
    }
}

// ** TARGETING **

// Targets the space, updates its status, and returns the result (HIT or MISS).
TargetResult GridSpace::target() {
    if (this->wasTargeted())
        throw invalid_argument("Space already targeted.");
    else {
        this->status = SpaceStatus::TARGETED; // Mark as targeted.
        if (this->hasStud()) {
            this->stud->hit();       // Register a hit on the Stud.
            this->modifyLabel();     // Update labels.
            return TargetResult::HIT;
        } else {
            this->modifyLabel();     // Update labels for a miss.
            return TargetResult::MISS;
        }
    }
}
