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
    using std::out_of_range;

// ** CONSTRUCTORS AND DESTRUCTOR **

// Default constructor.
Player::Player() {}

// Constructor with player type.
Player::Player(PlayerType player_type) : type {player_type} {
    if (player_type == CPU) {
        this->name = "Camden"; // Default name for CPU.
    }
    this->grid = new Grid(player_type); // Initialize player's grid.
}

// Constructor with player type and name.
Player::Player(PlayerType player_type, string player_name) : type {player_type}, name {player_name} {
    this->grid = new Grid(player_type);
}

// Constructor with player type, name, and foe.
Player::Player(PlayerType player_type, string player_name, Player* the_foe) 
    : type {player_type}, name {player_name} {
    this->grid = new Grid(player_type);
    this->makeFoe(the_foe); // Assign the foe.
}

// Destructor to clean up resources.
Player::~Player() {
    this->floatingShips.clear();
    this->sunkenShips.clear();
    for (size_t i = 0; i < this->ships.size(); ++i) {
        delete this->ships[i];
        this->ships[i] = nullptr;
    }
    delete this->grid;
    this->grid = nullptr;
    this->foe = nullptr;
    this->foeGrid = nullptr;
}

// ** GETTERS **

PlayerType Player::getPlayerType() const {
    return this->type;
}

string Player::getName() const {
    return this->name;
}

Grid* Player::getGrid() & {
    return this->grid;
}

Player* Player::getFoe() const {
    return this->foe;
}

Grid* Player::getFoeGrid() & {
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

// ** SETTERS **

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

// ** FOE MANAGEMENT **

// Sets the player's foe and assigns the foe's grid.
void Player::makeFoe(Player* &the_foe) {
    this->foe = the_foe;
    this->foeGrid = the_foe->getGrid();
}

// ** SHIP MANAGEMENT **

bool Player::hasShip(Ship* ship) const {
    for (Ship* the_ship : this->ships)
        if (ship == the_ship)
            return true;
    return false;
}

bool Player::shipIsFloating(Ship* ship) const {
    if (!this->hasShip(ship))
        return false;
    for (Ship* the_ship : this->floatingShips)
        if (ship == the_ship)
            return true;
    return false;
}

bool Player::shipIsSunken(Ship* ship) const {
    if (!this->hasShip(ship))
        return false;
    for (Ship* the_ship : this->sunkenShips)
        if (ship == the_ship)
            return true;
    return false;
}

void Player::stillFloating() const {
    cout << "\nShips still afloat:\n";
    for (Ship* ship : this->floatingShips)
        cout << ship->getShipName() << endl;
    cout << endl;
}

void Player::notSunkYet() const {
    cout << "\nOpponent's ships still afloat:\n";
    for (Ship* ship : this->foe->getFloatingShips())
        cout << ship->getShipName() << endl;
    cout << endl;
}

// Marks a ship as sunk and moves it to the sunken ships list.
void Player::sinkShip(Ship* ship) {
    if (!(this->hasShip(ship) && this->shipIsFloating(ship))) {
        cout << "Oopsie." << endl;
        return;
    }
    for (size_t i = 0; i < this->floatingShips.size(); ++i) {
        if (this->floatingShips[i] == ship) {
            this->floatingShips.erase(this->floatingShips.begin() + i);
            this->sunkenShips.push_back(ship);
        }
    }
}

// Checks if all the player's ships are sunk.
bool Player::allShipsAreSunk() const {
    return this->floatingShips.empty() && this->sunkenShips.size() == 5;
}

// ** TARGETING **

// Targets an opponent's grid and returns the result.
bool Player::target(string space, bool do_cout) {
    if (this->foeGrid == nullptr)
        throw domain_error("Foe grid not set.");
    if (!Spaces::isSpaceString(space)) {
        if (do_cout) cout << "Invalid entry." << endl;
        return false;
    }
    if (this->spaceWasTargeted(space)) {
        if (do_cout) cout << "Space already targeted." << endl;
        return false;
    }

    TargetResult shot;
    try {
        shot = this->foeGrid->target(space);
    } catch (std::exception& e) {
        cout << e.what() << endl;
        return false;
    }

    this->targetedSpaces.push_back(space);
    if (!do_cout) cout << space << endl;

    switch (shot) {
        case MISS:
            this->missSpaces.push_back(space);
            this->HMHist.push_back('M');
            cout << "Miss" << endl;
            break;

        case HIT:
            this->hitSpaces.push_back(space);
            this->HMHist.push_back('H');
            cout << "Hit" << endl;
            Ship* sunk_ship = this->foe->justSunkenShip();
            if (sunk_ship != nullptr) {
                cout << this->foe->getName() << "'s " << sunk_ship->getShipName() << " has been sunk!" << endl;
                this->foe->sinkShip(sunk_ship);
            }
            break;
    }

    return true;
}

// Processes input for special commands or targeting.
bool Player::processInput(string input) {
    if (input == "unsunk") {
        this->notSunkYet();
        return false;
    } else if (input == "afloat") {
        this->stillFloating();
        return false;
    } else if (input == "foe") {
        this->foeGrid->showGrid();
        return false;
    } else if (input == "own") {
        this->grid->showGrid();
        return false;
    } else {
        return this->target(input);
    }
}

// ** SHIP PLACEMENT **

// Allows the player to manually place all ships.
void Player::manuallySetShips() {
    this->setCarrier();
    this->setBattleship();
    this->setDestroyer();
    this->setSubmarine();
    this->setCruiser();
}

// Automatically places ships on the grid.
void Player::autoSetShips(int(*rand_func)()) {
    this->autoSetShip('A', rand_func);
    this->autoSetShip('B', rand_func);
    this->autoSetShip('D', rand_func);
    this->autoSetShip('S', rand_func);
    this->autoSetShip('C', rand_func);
}

// Asks the player whether to auto-place ships or manually place them.
void Player::askToSetShips(int(*rand_func)()) {
    char response;
    cout << "Auto set ships? (y/n) > ";
    cin >> response;
    while (!(response == 'y' || response == 'n')) {
        cout << "Invalid response. Please enter y or n." << endl;
        cout << "Auto set ships? (y/n) > ";
        cin >> response;
    }
    if (response == 'y') {
        this->autoSetShips(rand_func);
    } else {
        this->manuallySetShips();
    }
}

// Handles the player's turn.
void Player::doTurn() {
    bool input_result;
    do {
        string user_input;
        cout << "> ";
        cin >> user_input;
        input_result = this->processInput(user_input);
    } while (!input_result);
}
