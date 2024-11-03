#include "Player.h" // Include Player header file.

#include "Battleship.h" // Include for Battleship class.
#include "Carrier.h" // Include for Carrier class.
#include "Cruiser.h" // Include for Cruiser class.
#include "Destroyer.h" // Include for Destroyer class.
#include "Enums.h" // Include for enumerated types used in the class.
#include "Grid.h" // Include for Grid class.
#include "Ship.h" // Include for Ship base class.
#include "Submarine.h" // Include for Submarine class.

#include <string> // Include for using string class.
    using std::string; // Use string from the standard namespace.

#include <iostream> // Include for input-output operations.
    using std::cout; // Use cout for console output.
    using std::cin; // Use cin for console input.
    using std::endl; // Use endl for line breaks.

#include <array> // Include for using array class.
    using std::array; // Use array from the standard namespace.

#include <vector> // Include for using vector class.
    using std::vector; // Use vector from the standard namespace.

#include <stdexcept> // Include for handling exceptions.
    using std::domain_error; // Use domain_error from the standard namespace.
    using std::out_of_range; // Use out_of_range from the standard namespace.

// Default constructor.
Player::Player() {}

// Constructor: Initializes a Player with a specific PlayerType.
Player::Player(PlayerType player_type) : type{player_type} {
    if (player_type == CPU) {
        this->name = "Camden"; // Default name for the CPU player.
    }
    this->grid = new Grid(player_type); // Create a new Grid for the player.
}

// Constructor: Initializes a Player with a PlayerType and name.
Player::Player(PlayerType player_type, string player_name) : type{player_type}, name{player_name} {
    this->grid = new Grid(player_type); // Create a new Grid for the player.
}

// Constructor: Initializes a Player with a PlayerType, name, and sets the opponent.
Player::Player(PlayerType player_type, string player_name, Player* the_foe) : type{player_type}, name{player_name} {
    this->grid = new Grid(player_type); // Create a new Grid for the player.
    this->makeFoe(the_foe); // Set the opponent.
}

// Destructor: Cleans up dynamically allocated resources.
Player::~Player() {
    this->floatingShips.clear(); // Clear floating ships list.
    this->sunkenShips.clear(); // Clear sunken ships list.
    for(size_t i = 0; i < this->ships.size(); ++i) {
        delete this->ships[i]; // Delete each ship.
        this->ships[i] = nullptr; // Set pointer to nullptr.
    }
    delete this->grid; // Delete the grid.
    this->grid = nullptr; // Set grid pointer to nullptr.
    this->foe = nullptr; // Set foe pointer to nullptr.
    this->foeGrid = nullptr; // Set foeGrid pointer to nullptr.
}

// Getter: Returns the PlayerType of the Player.
PlayerType Player::getPlayerType() const {
    return this->type;
}

// Getter: Returns the name of the Player.
string Player::getName() const {
    return this->name;
}

// Getter: Returns the Grid of the Player.
Grid* Player::getGrid() const {
    return this->grid;
}

// Getter: Returns the Player's opponent.
Player* Player::getFoe() const {
    return this->foe;
}

// Getter: Returns the Grid of the Player's opponent.
Grid* Player::getFoeGrid() const {
    return this->foeGrid;
}

// Getter: Returns the array of ships owned by the Player.
array<Ship*, 5> Player::getShips() const {
    return this->ships;
}

// Getter: Returns the vector of floating (not yet sunk) ships.
vector<Ship*> Player::getFloatingShips() const {
    return this->floatingShips;
}

// Getter: Returns the vector of sunken ships.
vector<Ship*> Player::getSunkenShips() const {
    return this->sunkenShips;
}

// Getter: Returns the vector of spaces that have been targeted.
vector<string> Player::getTargetedSpaces() const {
    return this->targetedSpaces;
}

// Getter: Returns the vector of spaces where hits were recorded.
vector<string> Player::getHitSpaces() const {
    return this->hitSpaces;
}

// Getter: Returns the vector of spaces where misses were recorded.
vector<string> Player::getMissSpaces() const {
    return this->missSpaces;
}

// Getter: Returns the history of hits and misses ('H' for hit, 'M' for miss).
vector<char> Player::getHMHist() const {
    return this->HMHist;
}

// Setter: Sets the PlayerType of the Player.
void Player::setPlayerType(PlayerType player_type) {
    this->type = player_type;
}

// Setter: Sets the name of the Player.
void Player::setName(string player_name) {
    this->name = player_name;
}

// Setter: Sets the opponent of the Player.
void Player::setFoe(Player* the_foe) {
    this->foe = the_foe;
}

// Setter: Sets the Grid of the opponent.
void Player::setFoeGrid(Grid* the_grid) {
    this->foeGrid = the_grid;
}

// Method: Sets the opponent and links their grid to the Player.
void Player::makeFoe(Player* the_foe) {
    this->foe = the_foe;
    this->foeGrid = the_foe->getGrid(); // Link the opponent's grid.
}

// Method: Checks if the Player owns a specific ship.
bool Player::hasShip(Ship* ship) const {
    for (Ship* the_ship : this->ships)
        if(ship == the_ship)
            return true;
    return false;
}

// Method: Checks if a specific ship is floating (not sunk).
bool Player::shipIsFloating(Ship* ship) const {
    if(!this->hasShip(ship))
        return false;
    for (Ship* the_ship : this->floatingShips)
        if(ship == the_ship)
            return true;
    return false;
}

// Method: Checks if a specific ship is sunken.
bool Player::shipIsSunken(Ship* ship) const {
    if(!this->hasShip(ship))
        return false;
    for (Ship* the_ship : this->sunkenShips)
        if(ship == the_ship)
            return true;
    return false;
}

// Method: Prints the names of ships still afloat.
void Player::stillFloating() const {
    for(Ship* ship : this->floatingShips)
        cout << ship->getShipName() << endl;
}

// Method: Prints the names of the opponent's ships that are still afloat.
void Player::notSunkYet() const {
    for(Ship* ship : this->foe->getFloatingShips())
        cout << ship->getShipName() << endl;
}

// Method: Displays the opponent's grid.
void Player::showFoe() const {
    this->foeGrid->showGrid();
}

// Method: Displays the Player's own grid.
void Player::showOwn() const {
    this->grid->showGrid();
}

// Method: Returns a pointer to the ship that was just sunk, if any.
Ship* Player::justSunkenShip() const {
    for(Ship* ship : this->floatingShips)
        if(ship->wasSunk())
            return ship;
    return nullptr;
}

// Method: Marks a ship as sunken and updates the lists.
void Player::sinkShip(Ship* ship) {
    if(!(this->hasShip(ship) && this->shipIsFloating(ship)))
        return;
    for(size_t i = 0; i < this->floatingShips.size(); ++i)
        if(this->floatingShips[i] == ship) {
            this->floatingShips.erase(this->floatingShips.begin() + i); // Remove from floating list.
            this->sunkenShips.push_back(ship); // Add to sunken list.
        }
}

// Method: Checks if a specific space has already been targeted.
bool Player::spaceWasTargeted(string space) const {
    for(string the_space : this->targetedSpaces)
        if(space == the_space)
            return true;
    return false;
}

// Method: Targets a specific space on the opponent's grid.
bool Player::target(string space) {
    if(this->foeGrid == nullptr)
        throw domain_error("Foe grid not set.");
    if(!Spaces::isSpaceString(space)) {
        cout << "Invalid entry." << endl;
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

// Method: Processes user input and determines the appropriate action.
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

// Method: Checks if all ships are sunk.
bool Player::allShipsAreSunk() const {
    return !this->floatingShips.size() && this->sunkenShips.size() == 5;
} 

// Method: Sets up the Carrier ship manually.
void Player::setCarrier() {
    Carrier* carrier = new Carrier(this->grid);
    do {
        string start_space;
        char direction;
        cout << "Enter Carrier Start Space: ";
        cin >> start_space;
        while(!Spaces::isSpaceString(start_space)) {
            cout << "Invalid Space." << endl;
            cout << "Enter Carrier Start Space: ";
            cin >> start_space;
        }
        cout << "Enter Carrier Direction: ";
        cin >> direction;
        while (!(direction == 'N' || direction == 'S' || direction == 'E' || direction == 'W')) {
            cout << "Invalid Direction." << endl;
            cout << "Enter Carrier Direction: ";
            cin >> direction;
        }
        carrier->setIsReady(carrier->placeOnGrid(start_space, direction));
    } while (!carrier->getIsReady());
    this->ships[0] = carrier;
    this->floatingShips.push_back(carrier);
    cout << "" << endl;
    this->grid->showGrid();
    cout << "" << endl;
}

// Method: Sets up the Battleship ship manually.
void Player::setBattleship() {
    Battleship* battleship = new Battleship(this->grid);
    do {
        string start_space;
        char direction;
        cout << "Enter Battleship Start Space: ";
        cin >> start_space;
        while(!Spaces::isSpaceString(start_space) || this->grid->isNoGoSpace(start_space)) {
            if(!Spaces::isSpaceString(start_space))
                cout << "Invalid Space." << endl;
            else
                cout << "Space is occupied by or adjacent to an existing Ship. Please choose another space." << endl;
            cout << "Enter Battleship Start Space: ";
            cin >> start_space;
        }
        cout << "Enter Battleship Direction: ";
        cin >> direction;
        while (!(direction == 'N' || direction == 'S' || direction == 'E' || direction == 'W')) {
            cout << "Invalid Direction." << endl;
            cout << "Enter Battleship Direction: ";
            cin >> direction;
        }
        battleship->setIsReady(battleship->placeOnGrid(start_space, direction));
    } while (!battleship->getIsReady());
    this->ships[1] = battleship;
    this->floatingShips.push_back(battleship);
    cout << "" << endl;
    this->grid->showGrid();
    cout << "" << endl;
}

// Method: Sets up the Destroyer ship manually.
void Player::setDestroyer() {
    Destroyer* destroyer = new Destroyer(this->grid);
    do {
        string start_space;
        char direction;
        cout << "Enter Destroyer Start Space: ";
        cin >> start_space;
        while(!Spaces::isSpaceString(start_space) || this->grid->isNoGoSpace(start_space)) {
            if(!Spaces::isSpaceString(start_space))
                cout << "Invalid Space." << endl;
            else
                cout << "Space is occupied by or adjacent to an existing Ship. Please choose another space." << endl;
            cout << "Enter Destroyer Start Space: ";
            cin >> start_space;
        }
        cout << "Enter Destroyer Direction: ";
        cin >> direction;
        while (!(direction == 'N' || direction == 'S' || direction == 'E' || direction == 'W')) {
            cout << "Invalid Direction." << endl;
            cout << "Enter Destroyer Direction: ";
            cin >> direction;
        }
        destroyer->setIsReady(destroyer->placeOnGrid(start_space, direction));
    } while (!destroyer->getIsReady());
    this->ships[2] = destroyer;
    this->floatingShips.push_back(destroyer);
    cout << "" << endl;
    this->grid->showGrid();
    cout << "" << endl;
}

// Method: Sets up the Submarine ship manually.
void Player::setSubmarine() {
    Submarine* submarine = new Submarine(this->grid);
    do {
        string start_space;
        char direction;
        cout << "Enter Submarine Start Space: ";
        cin >> start_space;
        while(!Spaces::isSpaceString(start_space) || this->grid->isNoGoSpace(start_space)) {
            if(!Spaces::isSpaceString(start_space))
                cout << "Invalid Space." << endl;
            else
                cout << "Space is occupied by or adjacent to an existing Ship. Please choose another space." << endl;
            cout << "Enter Submarine Start Space: ";
            cin >> start_space;
        }
        cout << "Enter Submarine Direction: ";
        cin >> direction;
        while (!(direction == 'N' || direction == 'S' || direction == 'E' || direction == 'W')) {
            cout << "Invalid Direction." << endl;
            cout << "Enter Submarine Direction: ";
            cin >> direction;
        }
        submarine->setIsReady(submarine->placeOnGrid(start_space, direction));
    } while (!submarine->getIsReady());
    this->ships[3] = submarine;
    this->floatingShips.push_back(submarine);
    cout << "" << endl;
    this->grid->showGrid();
    cout << "" << endl;
}

// Method: Sets up the Cruiser ship manually.
void Player::setCruiser() {
    Cruiser* cruiser = new Cruiser(this->grid);
    do {
        string start_space;
        char direction;
        cout << "Enter Cruiser Start Space: ";
        cin >> start_space;
        while(!Spaces::isSpaceString(start_space) || this->grid->isNoGoSpace(start_space)) {
            if(!Spaces::isSpaceString(start_space))
                cout << "Invalid Space." << endl;
            else
                cout << "Space is occupied by or adjacent to an existing Ship. Please choose another space." << endl;
            cout << "Enter Cruiser Start Space: ";
            cin >> start_space;
        }
        cout << "Enter Cruiser Direction: ";
        cin >> direction;
        while (!(direction == 'N' || direction == 'S' || direction == 'E' || direction == 'W')) {
            cout << "Invalid Direction." << endl;
            cout << "Enter Cruiser Direction: ";
            cin >> direction;
        }
        cruiser->setIsReady(cruiser->placeOnGrid(start_space, direction));
    } while (!cruiser->getIsReady());
    this->ships[4] = cruiser;
    this->floatingShips.push_back(cruiser);
    cout << "" << endl;
    this->grid->showGrid();
    cout << "" << endl;
}

// Method: Manually sets up all ships for the player.
void Player::manuallySetShips() {
    this->setCarrier();
    this->setBattleship();
    this->setDestroyer();
    this->setSubmarine();
    this->setCruiser();
}

// Method: Automatically places a ship on the grid.
void Player::autoPutShip(Ship* ship, int(*rand_func)()) {
    char directions[] = {'N', 'S', 'E', 'W'};
    while(!ship->getIsReady()) {
        string start_space = Spaces::spaceStrings[static_cast<size_t>(rand_func() % 100)];
        char direction = directions[static_cast<size_t>(rand_func() % 4)];
        ship->setIsReady(ship->placeOnGrid(start_space, direction, false));
    }
    this->ships[static_cast<size_t>(ship->getShipType()) - 1] = ship;
    this->floatingShips.push_back(ship);
}

// Method: Automatically sets a specific ship on the grid based on its type.
void Player::autoSetShip(char ship_char, int(*rand_func)()) {
    switch (ship_char) {
        case 'A': {
            this->autoPutShip(new Carrier(this->grid), rand_func);
            break;
        }
        case 'B': {
            this->autoPutShip(new Battleship(this->grid), rand_func);
            break;
        }
        case 'C': {
            this->autoPutShip(new Cruiser(this->grid), rand_func);
            break;
        }
        case 'D': {
            this->autoPutShip(new Destroyer(this->grid), rand_func);
            break;
        }
        case 'S': {
            this->autoPutShip(new Submarine(this->grid), rand_func);
            break;
        }
    }
}

// Method: Automatically sets up all ships for the player.
void Player::autoSetShips(int(*rand_func)()) {
    this->autoSetShip('A', rand_func);
    this->autoSetShip('B', rand_func);
    this->autoSetShip('D', rand_func);
    this->autoSetShip('S', rand_func);
    this->autoSetShip('C', rand_func);
}

// Method: Asks the player if they want to auto-set ships or place them manually.
void Player::askToSetShips(int(*rand_func)()) {
    char response;
    cout << "Auto set ships ? (y/n) > ";
    cin >> response;
    while (!(response == 'y' || response == 'n')) {
        cout << "Invalid response. Please enter y or n." << endl;
        cout << "Auto set ships (y/n) > ";
        cin >> response;
    }
    if(response == 'y')
        this->autoSetShips(rand_func);
    else
        this->manuallySetShips();
}

// Method: Handles a player's turn by processing input and executing actions.
void Player::doTurn() {
    bool input_result;
    do {
        string user_input;
        cout << "> ";
        cin >> user_input;
        input_result = this->processInput(user_input);
    } while(!input_result);
}
