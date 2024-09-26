#include "Ship.h"

#include "Enums.h"
#include "Grid.h"

#include <string>
    using std::string;

#include <vector>
    using std::vector;

Ship::Ship() {}

Ship::Ship(ShipType ship_type) : shipType{ship_type} {}

Ship::Ship(ShipType ship_type, PlayerType of_player) : shipType {ship_type}, ofPlayer {of_player} {}

Ship::Ship(ShipType ship_type, Grid* on_grid) : shipType {ship_type}, onGrid {on_grid}
{
    this->ofPlayer = on_grid->getOfPlayer();
}

Ship::~Ship() {
    this->onGrid = nullptr;
    for(Stud* &intact_stud : this->intactStuds)
        intact_stud = nullptr;
    for(Stud* &destroyed_stud : this->destroyedStuds)
        destroyed_stud = nullptr;
}

PlayerType Ship::getOfPlayer() const {
    return this->ofPlayer;
}

Grid* Ship::getOnGrid() const {
    return this->onGrid;
}

vector<Stud*> Ship::getIntactSutds() const {
    return this->intactStuds;
}

vector<Stud*> Ship::getDestroyedStuds() const {
    return this->destroyedStuds;
}

ShipType Ship::getShipType() const {
    return this->shipType;
}

ShipStatus Ship::getShipStatus() const {
    return this->status;
}

bool Ship::getIsOnGrid() const {
    return this->isOnGrid;
}

void Ship::setOfPlayer(PlayerType of_player) {
    this->ofPlayer = of_player;
}

void Ship::setGrid(Grid* on_grid) {
    this->onGrid = on_grid;
}

void Ship::setShipType(ShipType ship_type) {
    this->shipType = ship_type;
}

void Ship::setShipStatus(ShipStatus ship_status) {
    this->status = ship_status;
}

void Ship::setIsOnGrid(bool is_on_grid) {
    this->isOnGrid = is_on_grid;
}

bool Ship::studIsIntact(Stud* stud) const {
    for(Stud* the_stud : this->intactStuds)
        if (the_stud == stud)
            return true;
    return false;
}

void Ship::destroyStud(Stud* stud) {
    if(!this->hasStud(stud))
        return;
    if(!this->studIsIntact(stud))
        return;
    for(size_t i=0; i < this->intactStuds.size(); ++i) {
        if(this->intactStuds[i] == stud) {
            this->intactStuds.erase(this->intactStuds.begin() + i);
            break;
        }
    }
    this->destroyedStuds.push_back(stud);
}
