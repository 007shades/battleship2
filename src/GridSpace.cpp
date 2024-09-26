#include "GridSpace.h"

#include "Enums.h"
#include "Stud.h"

#include <string>
    using std::string;

#include <stdexcept>
    using std::out_of_range;
    using std::invalid_argument;

    
void GridSpace::set_space_data(SpaceName space_name) {
    string space_string = Spaces::stringFromName(space_name);
    char letter = space_string.at(0);
    char number = space_string.length() == 3 ? '0' : space_string.at(1);
    this->spaceString = space_string;
    this->letter = letter;
    this->number = number;
    this->column = Spaces::columnFromChar(letter);
    this->row = Spaces::rowFromChar(number);
}

GridSpace::GridSpace() {}

GridSpace::GridSpace(SpaceName space_name) : spaceName{space_name} 
{
    this->set_space_data(space_name);
}

GridSpace::GridSpace(SpaceName space_name, PlayerType of_player) : spaceName{space_name}, ofPlayer{of_player}
{
    this->set_space_data(space_name);
}

GridSpace::GridSpace(SpaceName space_name, PlayerType of_player, SpaceStatus space_status) : spaceName{space_name}, ofPlayer{of_player}, status{space_status}
{
    this->set_space_data(space_name);
}

GridSpace::GridSpace(SpaceName space_name, PlayerType of_player, SpaceStatus space_status, Stud* the_stud) : spaceName{space_name}, ofPlayer{of_player}, status{space_status}, stud{the_stud}
{
    this->set_space_data(space_name);
}

GridSpace::~GridSpace() {
    this->stud = nullptr;
}

SpaceName GridSpace::getSpaceName() const {
    return this->spaceName;
}

Column GridSpace::getColumn() const {
    return this->column;
}

Row GridSpace::getRow() const {
    return this->row;
}

PlayerType GridSpace::getOfPlayer() const {
    return this->ofPlayer;
}

SpaceStatus GridSpace::getStatus() const {
    return this->status;
}

Stud* GridSpace::getStud() const {
    return this->stud;
}

string GridSpace::getSpaceString() const {
    return this->spaceString;
}

char GridSpace::getLetter() const {
    return this->letter;
}

char GridSpace::getNumber() const {
    return this->number;
}

char GridSpace::getLabel() const {
    return this->label;
}

void GridSpace::setSpaceName(SpaceName space_name) {
    this->spaceName = space_name;
    this->set_space_data(space_name);
}

void GridSpace::setOfPlayer(PlayerType of_player) {
    this->ofPlayer = of_player;
}

void GridSpace::setStatus(SpaceStatus space_status) {
    this->status = space_status;
}

void GridSpace::setStud(Stud* the_stud) {
    this->stud = the_stud;
}

void GridSpace::setLabel(char label) {
    this->label = label;
}

void GridSpace::addStud(Stud* the_stud) {
    if(this->hasStud())
        throw invalid_argument("Space already occupied.");
    this->stud = the_stud;
    this->label = the_stud->getLabel();
}

bool GridSpace::hasStud() const {
    return this->stud != nullptr;
}

bool GridSpace::wasTargeted() const {
    return this->status == SpaceStatus::TARGETED;
}

void GridSpace::modifyLabel() {
    if(this->ofPlayer == PlayerType::CPU)
        this->label = this->ofPlayer == this->hasStud() ? 'H' : 'M';
    else {
        if(this->hasStud())
            this->label = this->stud->getLabel();
        else this->label = '@';
    }
}

TargetResult GridSpace::target() {
    if(this->wasTargeted())
        throw out_of_range("Space already targeted.");
    this->status = SpaceStatus::TARGETED;
    if(this->hasStud()) {
        this->stud->hit();
        this->modifyLabel();
        return TargetResult::HIT;
    } else {
        this->modifyLabel(); 
        return TargetResult::MISS;
    }
}