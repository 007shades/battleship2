#include "Player.h"

#include "Battleship.h"
#include "Carrier.h"
#include "Cruiser.h"
#include "Destroyer.h"
#include "Enums.h"
#include "Grid.h"
#include "Ship.h"
#include "Submarine.h"

#include <string>
    using std::string;

#include <iostream>
    using std::cout;
    using std::cin;
    using std::endl;

#include <array>
    using std::array;

#include <vector>
    using std::vector;

#include <stdexcept>
    using std::domain_error;

#include <unistd.h> //Sleep function

Player::Player() {};

Player::Player(PlayerType player_type) : type {player_type} 
{
    if (player_type == CPU) {
        this->name = "Camden";
    }
}

Player::Player(PlayerType player_type, string player_name) : type {player_type}, name {player_name} {}

Player::Player(PlayerType player_type, string player_name, Player* the_foe) : type {player_type}, name {player_name} 
{
    this->makeFoe(the_foe);
}

Player::~Player() {
    this->floatingShips.clear();
    this->sunkenShips.clear();
    for(size_t i = 0; i < this->ships.size(); ++i) {
        delete this->ships[i];
        this->ships[i] = nullptr;
    }
    delete this->grid;
    this->grid = nullptr;
    this->foe = nullptr;
    this->foeGrid = nullptr;
}

PlayerType Player::getPlayerType() const {
    return this->type;
}

string Player::getName() const {
    return this->name;
}

Grid* Player::getGrid() const {
    return this->grid;
}

Player* Player::getFoe() const {
    return this->foe;
}

Grid* Player::getFoeGrid() const {
    return this->foeGrid;
}

array<Ship*, 5> Player::getShips() const {
    return this->ships;
}

vector<Ship*> Player::getFloatingShips() const {
    return this->floatingShips;
}

vector<Ship*> Player::getSunkenShips() const {
    return this->sunkenShips;
}

vector<string> Player::getTargetedSpaces() const {
    return this->targetedSpaces;
}

vector<string> Player::getHitSpaces() const {
    return this->hitSpaces;
}

vector<string> Player::getMissSpaces() const {
    return this->missSpaces;
}

vector<char> Player::getHMHist() const {
    return this->HMHist;
}

void Player::setPlayerType(PlayerType player_type) {
    this->type = player_type;
}

void Player::setName(string player_name) {
    this->name = player_name;
}

void Player::setFoe(Player* the_foe) {
    this->foe = the_foe;
}

void Player::setFoeGrid(Grid* the_grid) {
    this->foeGrid = the_grid;
}

void Player::makeFoe(Player* the_foe) {
    this->foe = the_foe;
    this->foeGrid = the_foe->getGrid();
}

bool Player::hasShip(Ship* ship) const {
    for (Ship* the_ship : this->ships)
        if(ship == the_ship)
            return true;
    return false;
}

bool Player::shipIsFloating(Ship* ship) const {
    if(!this->hasShip(ship))
        return false;
    for (Ship* the_ship : this->floatingShips)
        if(ship == the_ship)
            return true;
    return false;
}

bool Player::shipIsSunken(Ship* ship) const {
    if(!this->hasShip(ship))
        return false;
    for (Ship* the_ship : this->sunkenShips)
        if(ship == the_ship)
            return true;
    return false;
}

void Player::stillFloating() const {
    for(Ship* ship : this->floatingShips)
        cout << ship->getShipName() << endl;
}

void Player::notSunkYet() const {
    for(Ship* ship : this->foe->getFloatingShips())
        cout << ship->getShipName() << endl;
}

void Player::showFoe() const {
    this->foeGrid->showGrid();
}

void Player::showOwn() const {
    this->grid->showGrid();
}

Ship* Player::justSunkenShip() const {
    for(Ship* ship : this->floatingShips)
        if(ship->wasSunk())
            return ship;
    return nullptr;
}

void Player::sinkShip(Ship* ship) {
    if(!(this->hasShip(ship) && this->shipIsFloating(ship)))
        return;
    for(size_t i = 0; i < this->floatingShips.size(); ++i)
        if(this->floatingShips[i] == ship) {
            this->floatingShips.erase(this->floatingShips.begin() + i);
            this->sunkenShips.push_back(ship);
        }
}

bool Player::spaceWasTargeted(string space) const {
    for(string the_space : this->targetedSpaces)
        if(space == the_space)
            return true;
        
}

bool Player::target(string space) {
    if(this->foeGrid == nullptr)
        throw domain_error("Foe grid not set.");
    if(!Spaces::isSpaceString(space)) {
        cout << "Invalid space / command." << endl;
        return false;
    }
    if(this->spaceWasTargeted(space)) {
        cout << "Space already targeted." << endl;
        return false;
    }
    TargetResult shot = this->foeGrid->target(space);
    this->targetedSpaces.push_back(space);
    switch (shot) {
        case MISS: {
            this->missSpaces.push_back(space);
            this->HMHist.push_back('M');
            cout << "Miss" << endl;
            break;
        }
        case HIT: {
            this->hitSpaces.push_back(space);
            this->HMHist.push_back('H');
            cout << "Hit" << endl;
            Ship* sunk_ship = this->foe->justSunkenShip();
            if(sunk_ship != nullptr) {
                cout << this->foe->getName() << "\'s " << sunk_ship->getShipName() << " has been sunk!" << endl;
                this->foe->sinkShip(sunk_ship);
            }
            break;
        }
    };
    return true;
}

bool Player::processInput(string input) {
    if (input == "unsunk") {
        this->notSunkYet();
        return false;
    } else if (input == "afloat") {
        this->stillFloating();
        return false;
    } else if (input == "foe") {
        this->showFoe();
        return false;
    } else if(input == "own") {
        this->showOwn();
        return false;
    } else {
        return this->target(input);
    }
}

bool Player::allShipsAreSunk() const {
    return ! this->floatingShips.size() && this->sunkenShips.size() == 5;
} 

void Player::setCarrier() {
    Carrier* carrier = new Carrier(this->grid);
}