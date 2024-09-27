#include "Battleship.h"
#include "Ship.h"

#include "Enums.h"
#include "Grid.h"
#include "Stud.h"

#include <string>
    using std::string;

#include <array>
    using std::array;

#include <stdexcept>
    using std::out_of_range;

#include <iostream>
    using std::cout;
    using std::endl;

Battleship::Battleship() : Ship(ShipType::BATTLESHIP) {}

Battleship::Battleship(PlayerType of_player) : Ship(ShipType::BATTLESHIP, of_player) {}

Battleship::Battleship(Grid* on_grid) : Ship(ShipType::BATTLESHIP, on_grid) 
{
    this->setStuds();
}

Battleship::Battleship(Grid* on_grid, string start_space, char direction) : Ship (ShipType::BATTLESHIP, on_grid)
{
    this->setStuds();
    this->isReady = this->placeOnGrid(start_space, direction);
}

Battleship::~Battleship() {
    for(size_t i = 0; i < 4; ++i) {
        delete this->studs[i];
        this->studs[i] = nullptr;
    }
} 

array<Stud*, 4> Battleship::getStuds() const {
    return this->studs;
}

Stud* Battleship::getStud(StudName stud_name) const {
    for(Stud* stud : this->studs)
        if(stud->getStudName() == stud_name)
            return stud;
    return nullptr;
}

bool Battleship::hasStud(Stud* stud) const {
    for(Stud* the_stud : this->studs)
        if(the_stud == stud)
            return true;
    return false;
}

void Battleship::setStuds() {
    for(size_t i=5, j=0; i<9; i++, j++){
        this->studs[j] = new Stud(Studs::studNames[i], this->ofPlayer, this);
        this->intactStuds.push_back(this->studs[j]);
    }
}

bool Battleship::placeOnGrid(string start_space, char direction) const {
    vector<string> ship_spaces;
    try {
        ship_spaces = Grid::getVector(start_space, direction, 4);
    } catch (out_of_range& e) {
        cout << "Out of range." << endl;
        return false;
    }
    if(this->onGrid->hasNoGoSpace(ship_spaces)) {
        cout << "Ships cannot be touching." << endl;
        return false;
    }
    for(size_t i = 0; i < 4; i++)
        this->onGrid->setOnSpace(ship_spaces[i], this->studs[i]);
    vector<string> ship_neighbors = Grid::neighborSpaces(ship_spaces);
    this->onGrid->addNoGoSpaces(ship_spaces);
    this->onGrid->addNoGoSpaces(ship_neighbors);
    return true;
}