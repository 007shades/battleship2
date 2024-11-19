#include "Game.h"      // Includes the Game class header file.

#include "Camden.h"    // Includes the Camden AI class.
#include "Enums.h"     // Includes enumerations for PlayerType and other game-related enums.
#include "Player.h"    // Includes the Player class.

#include <string>      // Provides the string class.
    using std::string;

#include <iostream>    // Provides input/output utilities.
    using std::cout;
    using std::cin;
    using std::endl;

#include <unistd.h>    // Provides the sleep function.

#include <stdexcept>   // Provides standard exceptions like logic_error.
    using std::logic_error;

// ** CONSTRUCTORS AND DESTRUCTOR **

// Default constructor.
Game::Game() {}

// Constructor initializes the game with a human player.
Game::Game(string human_name) {
    this->cpu = new Player(CPU);           // Creates the CPU player.
    this->human = new Player(MAN, human_name); // Creates the human player.
}

// Constructor initializes the game with setup, coin toss, and gameplay.
Game::Game(string human_name, int(*rand_func)()) : Game(human_name) {
    this->doSetUp(rand_func);        // Sets up the game.
    this->doCoinToss(rand_func);     // Determines who goes first.
    this->doFinalSetup();            // Finalizes the setup (assign foes, etc.).
    this->playGame(rand_func);       // Starts the game loop.
}

// Destructor cleans up dynamically allocated resources.
Game::~Game() {
    delete this->human;
    this->human = nullptr;
    delete this->cpu;
    this->cpu = nullptr;
    delete this->camden;
    this->camden = nullptr;
}

// ** GETTERS AND SETTERS **

Player* Game::getHuman() const {
    return this->human; // Returns the human player.
}

Player* Game::getCpu() const {
    return this->cpu; // Returns the CPU player.
}

Camden* Game::getCamden() const {
    return this->camden; // Returns the Camden AI instance.
}

PlayerType Game::getTurn() const {
    return this->turn; // Returns the current turn.
}

void Game::setHuman(Player* the_human) {
    this->human = the_human; // Sets the human player.
}

void Game::setCpu(Player* the_cpu) {
    this->cpu = the_cpu; // Sets the CPU player.
}

void Game::setCamden(Camden* new_camden) {
    this->camden = new_camden; // Sets the Camden AI.
}

void Game::setTurn(PlayerType the_turn) {
    this->turn = the_turn; // Sets whose turn it is.
}

// ** GAME LOGIC **

// Checks if someone has won the game.
bool Game::someoneHasWon() const {
    return this->human->allShipsAreSunk() || this->cpu->allShipsAreSunk();
}

// Determines the winner.
PlayerType Game::winner() const {
    if (this->someoneHasWon()) {
        if (this->human->allShipsAreSunk())
            return CPU; // CPU wins.
        else
            return MAN; // Human wins.
    }
    throw logic_error("Nobody has won yet."); // Throws exception if no winner.
}

// Switches the turn to the other player.
void Game::switchTurn() {
    switch (this->turn) {
        case MAN:
            this->turn = CPU;
            break;
        case CPU:
        default:
            this->turn = MAN;
    }
}

// Handles the CPU's turn.
void Game::doCpuTurn(int(*rand_func)()) const {
    string bad_space = "NA";
    bool good_space_chosen = false;
    string camden_space;
    do {
        camden_space = this->camden->makeMove(rand_func, bad_space); // Camden picks a move.
        good_space_chosen = this->cpu->target(camden_space, false); // CPU attempts to target the space.
        if (!good_space_chosen) bad_space = camden_space; // If invalid, mark as "bad".
    } while (!good_space_chosen); // Repeat until a valid space is chosen.
}

// Handles the human player's turn.
void Game::doHumanTurn() const {
    this->human->doTurn(); // Executes the human's turn.
}

// Executes a turn for the current player.
void Game::doTurn(int(*rand_func)()) {
    if (this->turn == CPU)
        this->doCpuTurn(rand_func); // CPU's turn.
    else if (this->turn == MAN)
        this->doHumanTurn(); // Human's turn.
    else
        throw logic_error("It is nobody\'s turn."); // Throws an error if turn is invalid.
    this->switchTurn(); // Switches the turn to the other player.
}

// ** SETUP FUNCTIONS **

// Handles game setup for ships.
void Game::doSetUp(int(*rand_func)()) {
    this->human->askToSetShips(rand_func); // Prompts the human to place their ships.
    cout << "\nCamden is setting his ships..." << endl;
    this->cpu->autoSetShips(rand_func); // CPU places its ships automatically.
    sleep(1); // Pause for effect.
    cout << "   Done." << endl;
}

// Performs a coin toss to decide who goes first.
void Game::doCoinToss(int(*rand_func)()) {
    char user_coin_choice;
    cout << "Coin toss! Winner goes first. Heads or Tails?" << endl;
    cout << "(H / h or T / t) > ";
    cin >> user_coin_choice;
    int coin_toss = rand_func() % 2; // Simulates a coin toss (0 or 1).
    if (!coin_toss) { // Heads.
        if (user_coin_choice == 'H' || user_coin_choice == 'h') {
            cout << "It\'s Heads, you won the toss and will go first." << endl;
            this->turn = MAN;
        } else {
            cout << "It\'s Heads, you lost the toss and will go second." << endl;
            this->turn = CPU;
        }
    } else { // Tails.
        if (user_coin_choice == 'T' || user_coin_choice == 't') {
            cout << "It\'s Tails, you won the toss and will go first." << endl;
            this->turn = MAN;
        } else {
            cout << "It\'s Tails, you lost the toss and will go second." << endl;
            this->turn = CPU;
        }
    }
    sleep(1); // Pause for effect.
    cout << "Loading Game..." << endl;
    sleep(1);
}

// Finalizes setup by assigning foes to players and initializing Camden.
void Game::doFinalSetup() {
    this->human->makeFoe(this->cpu); // Sets CPU as human's foe.
    this->cpu->makeFoe(this->human); // Sets human as CPU's foe.
    this->camden = new Camden(this->cpu); // Initializes Camden AI.
}

// ** GAMEPLAY LOOP **

// Main game loop.
void Game::playGame(int(*rand_func)()) {
    do {
        cout << "" << endl;
        this->doTurn(rand_func); // Executes a turn.
        sleep(1); // Pause for effect.
        cout << "" << endl;
    } while (!this->someoneHasWon()); // Repeat until there's a winner.

    // Announce the winner.
    if (this->winner() == CPU) {
        cout << "Camden wins!" << endl;
        sleep(1);
        cout << "Here is Camden\'s grid: " << endl;
        this->cpu->getGrid()->showGrid(true); // Displays CPU's grid.
    } else {
        cout << "You win!" << endl;
    }
}
