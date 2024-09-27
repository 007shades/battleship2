#include "Cruiser.h"
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

Cruiser::Cruiser() : Ship(ShipType::CRUISER) {}

Cruiser::Cruiser(PlayerType of_player) : Ship(ShipType::CRUISER, of_player) {}

Cruiser::Cruiser(Grid* on_grid) : Ship(ShipType::CRUISER, on_grid) {}

Cruiser::Cruiser(Grid* on_grid, string start_space, char direction) : Ship (ShipType::BATTLESHIP, on_grid)
{
    this->setStuds();
    this->isReady = this->placeOnGrid(start_space, direction);
}


Cruiser::~Cruiser() {
    for(size_t i = 0; i < 2; ++i) {
        delete this->studs[i];
        this->studs[i] = nullptr;
    }
} 

array<Stud*, 2> Cruiser::getStuds() const {
    return this->studs;
}

Stud* Cruiser::getStud(StudName stud_name) const {
    for(Stud* stud : this->studs)
        if(stud->getStudName() == stud_name)
            return stud;
    return nullptr;
}

bool Cruiser::hasStud(Stud* stud) const {
    for(Stud* the_stud : this->studs)
        if(the_stud == stud)
            return true;
    return false;
}

void Cruiser::setStuds() {
    for(size_t i=15; i<17; i++)
        this->studs[i] = new Stud(Studs::studNames[i], this->ofPlayer, this);
}

bool Cruiser::placeOnGrid(string start_space, char direction) const {
    vector<string> ship_spaces;
    try {
        ship_spaces = Grid::getVector(start_space, direction, 2);
    } catch (out_of_range& e) {
        cout << "Out of range." << endl;
        return false;
    }
    if(this->onGrid->hasNoGoSpace(ship_spaces)) {
        cout << "Ships cannot be touching." << endl;
        return false;
    }
    for(size_t i = 0; i < 2; i++)
        this->onGrid->setOnSpace(ship_spaces[i], this->studs[i]);
    vector<string> ship_neighbors = Grid::neighborSpaces(ship_spaces);
    this->onGrid->addNoGoSpaces(ship_spaces);
    this->onGrid->addNoGoSpaces(ship_neighbors);
    return true;
}