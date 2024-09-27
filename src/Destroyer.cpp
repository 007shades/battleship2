#include "Destroyer.h"
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

Destroyer::Destroyer() : Ship(ShipType::DESTROYER) {}

Destroyer::Destroyer(PlayerType of_player) : Ship(ShipType::DESTROYER, of_player) {}

Destroyer::Destroyer(Grid* on_grid) : Ship(ShipType::DESTROYER, on_grid) 
{
    this->setStuds();
}

Destroyer::Destroyer(Grid* on_grid, string start_space, char direction) : Ship (ShipType::BATTLESHIP, on_grid)
{
    this->setStuds();
    this->isReady = this->placeOnGrid(start_space, direction);
}


Destroyer::~Destroyer() {
    for(size_t i = 0; i < 3; ++i) {
        delete this->studs[i];
        this->studs[i] = nullptr;
    }
} 

array<Stud*, 3> Destroyer::getStuds() const {
    return this->studs;
}

Stud* Destroyer::getStud(StudName stud_name) const {
    for(Stud* stud : this->studs)
        if(stud->getStudName() == stud_name)
            return stud;
    return nullptr;
}

bool Destroyer::hasStud(Stud* stud) const {
    for(Stud* the_stud : this->studs)
        if(the_stud == stud)
            return true;
    return false;
}

void Destroyer::setStuds() {
    for(size_t i=9, j=0; i<12; i++, j++){
        this->studs[j] = new Stud(Studs::studNames[i], this->ofPlayer, this);
        this->intactStuds.push_back(this->studs[j]);
    }
}

bool Destroyer::placeOnGrid(string start_space, char direction) const {
    vector<string> ship_spaces;
    try {
        ship_spaces = Grid::getVector(start_space, direction, 3);
    } catch (out_of_range& e) {
        cout << "Out of range." << endl;
        return false;
    }
    if(this->onGrid->hasNoGoSpace(ship_spaces)) {
        cout << "Ships cannot be touching." << endl;
        return false;
    }
    for(size_t i = 0; i < 3; i++)
        this->onGrid->setOnSpace(ship_spaces[i], this->studs[i]);
    vector<string> ship_neighbors = Grid::neighborSpaces(ship_spaces);
    this->onGrid->addNoGoSpaces(ship_spaces);
    this->onGrid->addNoGoSpaces(ship_neighbors);
    return true;
}