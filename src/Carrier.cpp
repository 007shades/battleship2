#include "Carrier.h"
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

Carrier::Carrier() : Ship(ShipType::CARRIER) {}

Carrier::Carrier(PlayerType of_player) : Ship(ShipType::CARRIER, of_player) {}

Carrier::Carrier(Grid* on_grid) : Ship(ShipType::CARRIER, on_grid) 
{
    this->setStuds();
}

Carrier::Carrier(Grid* on_grid, string start_space, char direction) : Ship (ShipType::BATTLESHIP, on_grid)
{
    this->setStuds();
    this->isReady = this->placeOnGrid(start_space, direction);
}


Carrier::~Carrier() {
    for(size_t i = 0; i < 5; ++i) {
        delete this->studs[i];
        this->studs[i] = nullptr;
    }
} 

array<Stud*, 5> Carrier::getStuds() const {
    return this->studs;
}

Stud* Carrier::getStud(StudName stud_name) const {
    for(Stud* stud : this->studs)
        if(stud->getStudName() == stud_name)
            return stud;
    return nullptr;
}

bool Carrier::hasStud(Stud* stud) const {
    for(Stud* the_stud : this->studs)
        if(the_stud == stud)
            return true;
    return false;
}

void Carrier::setStuds() {
    for(size_t i=0; i<5; i++){
        this->studs[i] = new Stud(Studs::studNames[i], this->ofPlayer, this);
        this->intactStuds.push_back(this->studs[i]);
    }
}

bool Carrier::placeOnGrid(string start_space, char direction, bool print_out) const {
    vector<string> ship_spaces;
    try {
        ship_spaces = Grid::getVector(start_space, direction, 4);
    } catch (out_of_range& e) {
        if(print_out)
            cout << "Out of range." << endl;
        return false;
    }
    if(this->onGrid->hasNoGoSpace(ship_spaces)) {
        if(print_out)
            cout << "Ships cannot be touching." << endl;
        return false;
    }
    for(size_t i = 0; i < 5; i++)
        this->onGrid->setOnSpace(ship_spaces[i], this->studs[i]);
    vector<string> ship_neighbors = Grid::neighborSpaces(ship_spaces);
    this->onGrid->addNoGoSpaces(ship_spaces);
    this->onGrid->addNoGoSpaces(ship_neighbors);
    return true;
}