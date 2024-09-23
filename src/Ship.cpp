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

