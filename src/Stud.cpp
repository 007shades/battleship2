#include "Stud.h"

#include "Enums.h"

#include <cctype>


void Stud::set_ship_type(StudName stud_name){
    int stud_int = static_cast<int>(stud_name);
    if (stud_int < 5) {
        this->forShip = Carrier;
        this->label = 'A';
    }
    else if (stud_int < 9) {
        this->forShip = Battleship;
        this->label = 'B';
    }
    else if (stud_int < 12) {
        this->forShip = Destroyer;
        this->label = 'D';
    }
    else if (stud_int < 15) {
        this->forShip = Submarine;
        this->label = 'S';
    }
    else {
        this->forShip = Cruiser;
        this->label = 'C';
    }
}

Stud::Stud() {}

Stud::Stud(StudName stud_name) : studName{stud_name} {
    set_ship_type(stud_name);
}

Stud::Stud(StudName stud_name, GridSpace* grid_space) : studName{stud_name}, gridspace {grid_space} 
{
    set_ship_type(stud_name);
    this->onSpace = grid_space->getSpaceName();
    this->ofPlayer = grid_space->getOfPlayer();
}

Stud::Stud(StudName stud_name, PlayerType of_player) : studName{stud_name}, ofPlayer {of_player}
{
    set_ship_type(stud_name);
}

Stud::Stud(StudName stud_name, GridSpace* grid_space, StudStatus the_status) : gridspace {grid_space}, status {the_status}
{
    set_ship_type(stud_name);
    this->onSpace = grid_space->getSpaceName();
    this->ofPlayer = grid_space->getOfPlayer();
}

Stud::Stud(StudName stud_name, PlayerType of_player, StudStatus the_status) : studName{stud_name}, ofPlayer{of_player}, status {the_status}
{
    set_ship_type(stud_name);
}

Stud::~Stud() {
    this->gridspace = nullptr;
}

StudName Stud::getStudName() const {
    return this->studName;
}

SpaceName Stud::getOnSpace() const {
    return this->onSpace;
}

ShipType Stud::getForShip() const {
    return this->forShip;
}

PlayerType Stud::getOfPlayer() const {
    return this->ofPlayer;
}

StudStatus Stud::getStatus() const {
    return this->status;
}

char Stud::getLabel() const {
    return this->label;
}

void Stud::setStudName(StudName stud_name) {
    this->studName = stud_name;
    this->set_ship_type(stud_name);
}

void Stud::setOnSpace(SpaceName on_space) {
    this->onSpace = on_space;
}

void Stud::setOfPlayer(PlayerType of_player) {
    this->ofPlayer = of_player;
}

void Stud::setStatus(StudStatus the_status) { 
    this->status = the_status;
}

void Stud::setLabel(char stud_label) {
    this->label = stud_label;
}

bool Stud::wasHit() const {
    return this->status == COMPROMISED;
}

void Stud::hit() {
    this->status = COMPROMISED;
    this->label = static_cast<char>(tolower(static_cast<unsigned char>(this->label)));
}