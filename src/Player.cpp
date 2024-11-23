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

// **Constructors and Destructor**

// Default constructor.
Player::Player() {}

// Constructor that initializes player type (CPU or MAN).
Player::Player(PlayerType player_type) : type {player_type} {
    if (player_type == CPU) {
        this->name = "Camden"; // Default name for CPU player.
    }
    this->grid = new Grid(player_type); // Initialize grid based on player type.
}

// Constructor that initializes player type and name.
Player::Player(PlayerType player_type, string player_name) : type {player_type}, name {player_name} {
    this->grid = new Grid(player_type); // Initialize grid.
}

// Constructor that initializes player type, name, and opponent.
Player::Player(PlayerType player_type, string player_name, Player* the_foe) : type {player_type}, name {player_name} {
    this->grid = new Grid(player_type); // Initialize grid.
    this->makeFoe(the_foe); // Set opponent.
}

// Destructor to clean up resources.
Player::~Player() {
    this->floatingShips.clear(); // Clear the list of floating ships.
    this->sunkenShips.clear(); // Clear the list of sunken ships.

    // Delete and nullify ships.
    for (size_t i = 0; i < this->ships.size(); ++i) {
        delete this->ships[i];
        this->ships[i] = nullptr;
    }

    delete this->grid; // Delete grid.
    this->grid = nullptr;

    this->foe = nullptr; // Nullify opponent reference.
    this->foeGrid = nullptr; // Nullify opponent's grid reference.
}

// **Getter and Setter Methods**
PlayerType Player::getPlayerType() const { return this->type; }
string Player::getName() const { return this->name; }
Grid* Player::getGrid() & { return this->grid; }
Player* Player::getFoe() const { return this->foe; }
Grid* Player::getFoeGrid() & { return this->foeGrid; }
array<Ship*, 5> Player::getShips() const { return this->ships; }
vector<Ship*> Player::getFloatingShips() const { return this->floatingShips; }
vector<Ship*> Player::getSunkenShips() const { return this->sunkenShips; }
vector<string> Player::getTargetedSpaces() const { return this->targetedSpaces; }
vector<string> Player::getHitSpaces() const { return this->hitSpaces; }
vector<string> Player::getMissSpaces() const { return this->missSpaces; }
vector<char> Player::getHMHist() const { return this->HMHist; }

void Player::setPlayerType(PlayerType player_type) { this->type = player_type; }
void Player::setName(string player_name) { this->name = player_name; }
void Player::setFoe(Player* the_foe) { this->foe = the_foe; }
void Player::setFoeGrid(Grid* the_grid) { this->foeGrid = the_grid; }

// Sets the player's opponent and their grid.
void Player::makeFoe(Player* &the_foe) {
    this->foe = the_foe;
    this->foeGrid = the_foe->getGrid();
}

// **Ship State and Status Methods**

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

// Prints a list of ships still afloat.
void Player::stillFloating() const {
    cout << "\nShips still afloat:\n";
    for (Ship* ship : this->floatingShips)
        cout << ship->getShipName() << endl;
    cout << endl;
}

// Prints a list of opponent's ships not sunk yet.
void Player::notSunkYet() const {
    cout << "\nOpponent's unsunk ships:\n";
    for (Ship* ship : this->foe->getFloatingShips())
        cout << ship->getShipName() << endl;
    cout << endl;
}

// Shows the opponent's grid.
void Player::showFoe() const {
    cout << "\nOpponent's grid:\n";
    this->foeGrid->showGrid();
    cout << endl;
}

// Shows the player's own grid.
void Player::showOwn() const {
    cout << "\nYour grid:\n";
    this->grid->showGrid();
    cout << endl;
}

// Checks if a space was already targeted.
bool Player::spaceWasTargeted(string space) const {
    for (string the_space : this->targetedSpaces)
        if (space == the_space)
            return true;
    return false;
}

// Processes the result of a targeting attempt.
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
    if (shot == MISS) {
        this->missSpaces.push_back(space);
        this->HMHist.push_back('M');
        cout << "Miss" << endl;
    } else if (shot == HIT) {
        this->hitSpaces.push_back(space);
        this->HMHist.push_back('H');
        cout << "Hit" << endl;
        Ship* sunk_ship = this->foe->justSunkenShip();
        if (sunk_ship != nullptr) {
            cout << this->foe->getName() << "'s " << sunk_ship->getShipName() << " has been sunk!" << endl;
            this->foe->sinkShip(sunk_ship);
        }
    }
    return true;
}

// **Gameplay Methods**

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
    } else if (input == "own") {
        this->showOwn();
        return false;
    } else {
        return this->target(input);
    }
}

bool Player::allShipsAreSunk() const {
    return this->floatingShips.empty() && this->sunkenShips.size() == 5;
}

// Sets up ships manually.
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

// Executes the player's turn.
void Player::doTurn() {
    bool input_result;
    do {
        string user_input;
        cout << "> ";
        cin >> user_input;
        input_result = this->processInput(user_input);
    } while (!input_result);
}
