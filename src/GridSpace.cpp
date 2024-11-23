#include "GridSpace.h"
#include "Enums.h"
#include "Stud.h"

#include <string>
    using std::string;

#include <stdexcept>
    using std::out_of_range;
    using std::invalid_argument;

// **Private Method**
// Sets up the attributes of the grid space based on the given `SpaceName`.
void GridSpace::set_space_data(SpaceName space_name) {
    string space_string = Spaces::stringFromName(space_name); // Converts `SpaceName` to string (e.g., "A1").
    char letter = space_string.at(0); // Extracts the column letter.
    char number = space_string.length() == 3 ? '0' : space_string.at(1); // Handles special case for row "10".
    
    // Initializes member variables.
    this->spaceString = space_string;
    this->letter = letter;
    this->number = number;
    this->column = Spaces::columnFromChar(letter); // Maps letter to column enum.
    this->row = Spaces::rowFromChar(number);       // Maps number to row enum.
}

// **Constructors**

// Default constructor.
GridSpace::GridSpace() {}

// Constructor with `SpaceName`.
GridSpace::GridSpace(SpaceName space_name) : spaceName{space_name} {
    this->set_space_data(space_name); // Initializes the grid space based on its name.
}

// Constructor with `SpaceName` and `PlayerType`.
GridSpace::GridSpace(SpaceName space_name, PlayerType of_player) 
    : spaceName{space_name}, ofPlayer{of_player} {
    this->set_space_data(space_name);
}

// Constructor with `SpaceName`, `PlayerType`, and initial space status.
GridSpace::GridSpace(SpaceName space_name, PlayerType of_player, SpaceStatus space_status) 
    : spaceName{space_name}, ofPlayer{of_player}, status{space_status} {
    this->set_space_data(space_name);
}

// Constructor with `SpaceName`, `PlayerType`, space status, and an associated `Stud`.
GridSpace::GridSpace(SpaceName space_name, PlayerType of_player, SpaceStatus space_status, Stud* the_stud) 
    : spaceName{space_name}, ofPlayer{of_player}, status{space_status}, stud{the_stud} {
    this->set_space_data(space_name);
}

// Destructor to clean up resources.
GridSpace::~GridSpace() {
    this->stud = nullptr; // Clears the pointer to avoid dangling references.
}

// **Getter Methods**
SpaceName GridSpace::getSpaceName() const { return this->spaceName; }
Column GridSpace::getColumn() const { return this->column; }
Row GridSpace::getRow() const { return this->row; }
PlayerType GridSpace::getOfPlayer() const { return this->ofPlayer; }
SpaceStatus GridSpace::getStatus() const { return this->status; }
Stud* GridSpace::getStud() const { return this->stud; }
string GridSpace::getSpaceString() const { return this->spaceString; }
char GridSpace::getLetter() const { return this->letter; }
char GridSpace::getNumber() const { return this->number; }
char GridSpace::getLabel() const { return this->label; }
char GridSpace::getPrimeLabel() const { return this->primeLabel; }

// **Setter Methods**
void GridSpace::setSpaceName(SpaceName space_name) {
    this->spaceName = space_name;
    this->set_space_data(space_name); // Recalculate space data based on new name.
}

void GridSpace::setOfPlayer(PlayerType of_player) { this->ofPlayer = of_player; }
void GridSpace::setStatus(SpaceStatus space_status) { this->status = space_status; }
void GridSpace::setStud(Stud* the_stud) { this->stud = the_stud; }
void GridSpace::setLabel(char label) { this->label = label; }

// Adds a `Stud` to this grid space.
void GridSpace::addStud(Stud* the_stud) {
    if (this->hasStud())
        throw invalid_argument("Space already occupied."); // Prevents multiple studs in the same space.

    this->stud = the_stud; // Associates the stud with this space.

    // Update labels based on the player type.
    if (this->ofPlayer == MAN)
        this->label = the_stud->getLabel(); // Display the stud's label.
    this->primeLabel = the_stud->getLabel();
}

// **State Check Methods**
bool GridSpace::hasStud() const { return this->stud != nullptr; }
bool GridSpace::wasTargeted() const { return this->status == SpaceStatus::TARGETED; }

// Modifies the label based on the space's state (e.g., hit, miss).
void GridSpace::modifyLabel() {
    if (this->ofPlayer == PlayerType::CPU) {
        this->label = this->hasStud() ? 'H' : 'M'; // 'H' for hit, 'M' for miss.
        this->primeLabel = this->hasStud() ? this->stud->getLabel() : '@'; // '@' for miss.
    } else {
        this->label = this->hasStud() ? this->stud->getLabel() : '@';
    }
}

// Targets this space during gameplay.
TargetResult GridSpace::target() {
    if (this->wasTargeted())
        throw invalid_argument("Space already targeted."); // Prevents retargeting the same space.

    // Mark space as targeted.
    this->status = SpaceStatus::TARGETED;

    if (this->hasStud()) {
        this->stud->hit();      // Marks the associated stud as hit.
        this->modifyLabel();    // Updates the label to reflect the hit.
        return TargetResult::HIT;
    } else {
        this->modifyLabel();    // Updates the label to reflect the miss.
        return TargetResult::MISS;
    }
}
