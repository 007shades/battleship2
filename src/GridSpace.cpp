#include "GridSpace.h" // Include GridSpace header file.

#include "Enums.h" // Include for enumerated types used in the class.
#include "Stud.h" // Include Stud class for representing ship parts.

#include <string> // Include for handling strings.
    using std::string; // Use string from the standard namespace.

#include <stdexcept> // Include for handling exceptions like out_of_range and invalid_argument.
    using std::out_of_range; // Use out_of_range from the standard namespace.
    using std::invalid_argument; // Use invalid_argument from the standard namespace.

// Method: Sets space data based on a given SpaceName.
void GridSpace::set_space_data(SpaceName space_name) {
    string space_string = Spaces::stringFromName(space_name); // Get string representation of the space.
    char letter = space_string.at(0); // Extract column letter.
    char number = space_string.length() == 3 ? '0' : space_string.at(1); // Extract row number ('10' as '0').
    this->spaceString = space_string; // Set spaceString member.
    this->letter = letter; // Set letter member.
    this->number = number; // Set number member.
    this->column = Spaces::columnFromChar(letter); // Convert letter to Column type.
    this->row = Spaces::rowFromChar(number); // Convert number to Row type.
}

// Default constructor.
GridSpace::GridSpace() {}

// Constructor: Initializes a GridSpace with a SpaceName.
GridSpace::GridSpace(SpaceName space_name) : spaceName{space_name} {
    this->set_space_data(space_name); // Set additional space data.
}

// Constructor: Initializes a GridSpace with a SpaceName and player type.
GridSpace::GridSpace(SpaceName space_name, PlayerType of_player) : spaceName{space_name}, ofPlayer{of_player} {
    this->set_space_data(space_name); // Set additional space data.
}

// Constructor: Initializes a GridSpace with a SpaceName, player type, and status.
GridSpace::GridSpace(SpaceName space_name, PlayerType of_player, SpaceStatus space_status) : spaceName{space_name}, ofPlayer{of_player}, status{space_status} {
    this->set_space_data(space_name); // Set additional space data.
}

// Constructor: Initializes a GridSpace with a SpaceName, player type, status, and Stud.
GridSpace::GridSpace(SpaceName space_name, PlayerType of_player, SpaceStatus space_status, Stud* the_stud) : spaceName{space_name}, ofPlayer{of_player}, status{space_status}, stud{the_stud} {
    this->set_space_data(space_name); // Set additional space data.
}

// Destructor: Cleans up resources used by the GridSpace.
GridSpace::~GridSpace() {
    this->stud = nullptr; // Set stud pointer to nullptr.
}

// Getter: Returns the SpaceName of the GridSpace.
SpaceName GridSpace::getSpaceName() const {
    return this->spaceName;
}

// Getter: Returns the Column of the GridSpace.
Column GridSpace::getColumn() const {
    return this->column;
}

// Getter: Returns the Row of the GridSpace.
Row GridSpace::getRow() const {
    return this->row;
}

// Getter: Returns the PlayerType associated with the GridSpace.
PlayerType GridSpace::getOfPlayer() const {
    return this->ofPlayer;
}

// Getter: Returns the SpaceStatus of the GridSpace.
SpaceStatus GridSpace::getStatus() const {
    return this->status;
}

// Getter: Returns a pointer to the Stud on the GridSpace.
Stud* GridSpace::getStud() const {
    return this->stud;
}

// Getter: Returns the string representation of the space.
string GridSpace::getSpaceString() const {
    return this->spaceString;
}

// Getter: Returns the column letter of the GridSpace.
char GridSpace::getLetter() const {
    return this->letter;
}

// Getter: Returns the row number character of the GridSpace.
char GridSpace::getNumber() const {
    return this->number;
}

// Getter: Returns the label of the GridSpace.
char GridSpace::getLabel() const {
    return this->label;
}

// Getter: Returns the prime label of the GridSpace (used for hidden state).
char GridSpace::getPrimeLabel() const {
    return this->primeLabel;
}

// Setter: Sets the SpaceName and updates space data accordingly.
void GridSpace::setSpaceName(SpaceName space_name) {
    this->spaceName = space_name; // Set the spaceName member.
    this->set_space_data(space_name); // Update additional space data.
}

// Setter: Sets the PlayerType associated with the GridSpace.
void GridSpace::setOfPlayer(PlayerType of_player) {
    this->ofPlayer = of_player;
}

// Setter: Sets the SpaceStatus of the GridSpace.
void GridSpace::setStatus(SpaceStatus space_status) {
    this->status = space_status;
}

// Setter: Sets the Stud on the GridSpace.
void GridSpace::setStud(Stud* the_stud) {
    this->stud = the_stud;
}

// Setter: Sets the label of the GridSpace.
void GridSpace::setLabel(char label) {
    this->label = label;
}

// Method: Adds a Stud to the GridSpace and updates labels.
void GridSpace::addStud(Stud* the_stud) {
    if(this->hasStud())
        throw invalid_argument("Space already occupied."); // Throw if space is already occupied.
    this->stud = the_stud; // Set the stud pointer.
    this->label = the_stud->getLabel(); // Update label.
    this->primeLabel = the_stud->getLabel(); // Update prime label.
}

// Method: Checks if the GridSpace has a Stud.
bool GridSpace::hasStud() const {
    return this->stud != nullptr; // Return true if stud is not null.
}

// Method: Checks if the GridSpace was targeted.
bool GridSpace::wasTargeted() const {
    return this->status == SpaceStatus::TARGETED; // Return true if status is TARGETED.
}

// Method: Modifies the label based on the targeting and ownership state.
void GridSpace::modifyLabel() {
    if(this->ofPlayer == PlayerType::CPU) {
        this->label = this->hasStud() ? 'H' : 'M'; // 'H' for hit, 'M' for miss.
        if(this->hasStud())
            this->primeLabel = this->stud->getLabel(); // Set prime label for hit.
        else
            this->primeLabel = '@'; // Set prime label for miss.
    }
    else {
        if(this->hasStud())
            this->label = this->stud->getLabel(); // Show stud's label if present.
        else
            this->label = '@'; // Set label for empty space.
    }
}

// Method: Targets the GridSpace and updates status and labels.
TargetResult GridSpace::target() {
    if(this->wasTargeted())
        throw out_of_range("Space already targeted."); // Throw if already targeted.
    this->status = SpaceStatus::TARGETED; // Set status to TARGETED.
    if(this->hasStud()) {
        this->stud->hit(); // Mark stud as hit.
        this->modifyLabel(); // Update labels.
        return TargetResult::HIT; // Return HIT result.
    } else {
        this->modifyLabel(); // Update labels for a miss.
        return TargetResult::MISS; // Return MISS result.
    }
}
