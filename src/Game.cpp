#include "Game.h"

#include "Camden.h"  // AI logic for the CPU player.
#include "Enums.h"   // Enumerations for player types and results.
#include "Player.h"  // Human and CPU player details.

#include <string>
    using std::string;

#include <iostream>
    using std::cout;
    using std::cin;
    using std::endl;

#include <unistd.h>  // For the sleep function, to create delays for a smoother user experience.

#include <stdexcept>
    using std::logic_error;

// **Default Constructor**
// Initializes a Game object without setting up players or starting the game.
Game::Game() {}

// **Single-Player Constructor**
// Initializes the game with a human player and a CPU opponent.
Game::Game(string human_name) {
    this->cpu = new Player(CPU);               // Create the CPU player.
    this->human = new Player(MAN, human_name); // Create the human player with the given name.
}

// **Game Setup Constructor**
// Initializes players, sets up the game, and starts gameplay.
Game::Game(string human_name, int(*rand_func)()) : Game(human_name) {
    this->doSetUp(rand_func);     // Set up the game (place ships).
    this->doCoinToss(rand_func);  // Decide who goes first with a coin toss.
    this->doFinalSetup();         // Finalize setup (link players and AI).
    this->playGame(rand_func);    // Start the game loop.
}

// **Destructor**
// Frees dynamically allocated memory for players and the AI.
Game::~Game() {
    delete this->human;  // Free memory for the human player.
    this->human = nullptr;
    delete this->cpu;    // Free memory for the CPU player.
    this->cpu = nullptr;
    delete this->camden; // Free memory for the AI logic.
    this->camden = nullptr;
}

// **Getter for Human Player**
Player* Game::getHuman() const {
    return this->human;
}

// **Getter for CPU Player**
Player* Game::getCpu() const {
    return this->cpu;
}

// **Getter for AI Logic**
Camden* Game::getCamden() const {
    return this->camden;
}

// **Getter for Current Turn**
PlayerType Game::getTurn() const {
    return this->turn;
}

// **Setter for Human Player**
void Game::setHuman(Player* the_human) {
    this->human = the_human;
}

// **Setter for CPU Player**
void Game::setCpu(Player* the_cpu) {
    this->cpu = the_cpu;
}

// **Setter for AI Logic**
void Game::setCamden(Camden* new_camden) {
    this->camden = new_camden;
}

// **Setter for Turn**
void Game::setTurn(PlayerType the_turn) {
    this->turn = the_turn;
}

// **Check if Someone has Won**
// Determines if either player has sunk all opponent ships.
bool Game::someoneHasWon() const {
    return this->human->allShipsAreSunk() || this->cpu->allShipsAreSunk();
}

// **Identify Winner**
// Returns the winner based on the state of the game.
PlayerType Game::winner() const {
    if(this->someoneHasWon()) {
        if(this->human->allShipsAreSunk())
            return CPU; // CPU wins if the human's ships are all sunk.
        else
            return MAN; // Human wins otherwise.
    }
    throw logic_error("Nobody has won yet."); // No winner if the game is still ongoing.
}

// **Switch Turn**
// Alternates between the human and CPU player.
void Game::switchTurn() {
    switch(this->turn) {
        case MAN:
            this->turn = CPU; // Switch to CPU's turn.
            break;
        case CPU:
        default:
            this->turn = MAN; // Switch to human's turn.
    }
}

// **CPU Turn Logic**
// Executes the CPU's turn using AI logic.
void Game::doCpuTurn(int(*rand_func)()) const {
    string bad_space = "NA"; // Placeholder for invalid spaces.
    bool good_space_chosen = false;
    string camden_space;
    do {
        camden_space = this->camden->makeMove(rand_func, bad_space); // AI chooses a space.
        good_space_chosen = this->cpu->target(camden_space, false);  // Try targeting that space.
        if(!good_space_chosen) bad_space = camden_space;            // Retry if the space was invalid.
    } while (!good_space_chosen);
}

// **Human Turn Logic**
// Prompts the human player to make their move.
void Game::doHumanTurn() const {
    this->human->doTurn();
}

// **Execute a Turn**
// Executes a turn for the current player and switches turns.
void Game::doTurn(int(*rand_func)()) {
    if(this->turn == CPU)
        this->doCpuTurn(rand_func); // CPU's turn.
    else if(this->turn == MAN)
        this->doHumanTurn(); // Human's turn.
    else
        throw logic_error("It is nobody\'s turn."); // Handle invalid states.
    this->switchTurn(); // Switch to the next player's turn.
}

// **Game Setup**
// Allows the human to place ships and auto-places ships for the CPU.
void Game::doSetUp(int(*rand_func)()) {
    this->human->askToSetShips(rand_func); // Human sets their ships.
    cout << "\nCamden is setting his ships..." << endl;
    this->cpu->autoSetShips(rand_func); // CPU's ships are auto-placed.
    sleep(1);
    cout << "   Done." << endl;
}

// **Coin Toss to Decide First Turn**
void Game::doCoinToss(int(*rand_func)()) {
    char user_coin_choice;
    cout << "" << endl;
    cout << "Coin toss! Winner goes first. Heads or Tails?" << endl;
    cout << "(H / h or T / t) > ";
    cin >> user_coin_choice;
    int coin_toss = rand_func() % 2; // Randomize coin toss.
    if (!coin_toss){
        if(user_coin_choice == 'H' || user_coin_choice == 'h') {
            cout << "It\'s Heads, you won the toss and will go first." << endl;
            this->turn = MAN;
        } else {
            cout << "It\'s Heads, you lost the toss and will go second." << endl;
            this->turn = CPU;
        }
    } else {
        if(user_coin_choice == 'T' || user_coin_choice == 't') {
            cout << "It\'s Tails, you won the toss and will go first." << endl;
            this->turn = MAN;
        } else {
            cout << "It\'s Tails, you lost the toss and will go second." << endl;
        }
    }
    sleep(1);
    cout << "" << endl;
    cout << "Loading Game..." << endl;
    sleep(1);
    cout << "" << endl;
}

// **Final Setup**
// Links players and initializes the AI for CPU logic.
void Game::doFinalSetup() {
    this->human->makeFoe(this->cpu); // Set CPU as human's foe.
    this->cpu->makeFoe(this->human); // Set human as CPU's foe.
    this->camden = new Camden(this->cpu); // Initialize AI for CPU.
}

// **Game Loop**
// Runs the main game loop until there is a winner.
void Game::playGame(int(*rand_func)()){
    do {
        cout << "" << endl;
        this->doTurn(rand_func); // Execute a turn.
        sleep(1); // Add delay for better pacing.
        cout << "" << endl;
    } while (!(this->someoneHasWon())); // Continue until there is a winner.

    // Announce the winner.
    if(this->someoneHasWon()){
        cout << "" << endl;
        if(this->winner() == CPU) {
            cout << "Camden wins!" << endl;
            sleep(1);
            cout << "" << endl;
            cout << "Here is Camden\'s grid: " << endl;
            cout << "" << endl;
            this->cpu->getGrid()->showGrid(true); // Show the CPU's grid.
        } else cout << "You win!" << endl;
    }
}
