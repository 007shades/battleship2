#include "Game.h" // Include Game header file.

#include "Camden.h" // Include Camden AI class.
#include "Enums.h" // Include Enums for predefined enumerations.
#include "Player.h" // Include Player class for handling player functionality.

#include <string> // Include string for handling text.
    using std::string; // Use string from the standard namespace.

#include <iostream> // Include for input-output operations.
    using std::cout; // Use cout for console output.
    using std::cin; // Use cin for console input.
    using std::endl; // Use endl for line breaks.

#include <unistd.h> // Include for sleep function to create delays.

#include <stdexcept> // Include for handling exceptions like logic_error.
    using std::logic_error; // Use logic_error from the standard namespace.

// Default constructor.
Game::Game() {}

// Constructor: Initializes the game with a human player name and sets up players and Camden AI.
Game::Game(string human_name) {
    this->cpu = new Player(CPU); // Create CPU player.
    this->human = new Player(MAN, human_name, this->cpu); // Create human player and associate with CPU.
    this->cpu->makeFoe(this->human); // Set human as the CPU's foe.
    this->camden = new Camden(this->cpu); // Initialize Camden AI with CPU player.
}

// Constructor: Initializes the game, sets up the game state, and starts the game loop.
Game::Game(string human_name, int(*rand_func)()) : Game(human_name) {
    this->doSetUp(rand_func); // Set up players' ships.
    this->doCoinToss(rand_func); // Perform a coin toss to decide the first turn.
    this->playGame(rand_func); // Start the game loop.
}

// Destructor: Cleans up dynamically allocated memory for players and Camden AI.
Game::~Game() {
    delete this->human; // Delete human player.
    this->human = nullptr; // Set pointer to nullptr to avoid dangling pointers.
    delete this->cpu; // Delete CPU player.
    this->cpu = nullptr; // Set pointer to nullptr.
    delete this->camden; // Delete Camden AI.
    this->camden = nullptr; // Set pointer to nullptr.
}

// Getter: Returns the human player.
Player* Game::getHuman() const {
    return this->human;
}

// Getter: Returns the CPU player.
Player* Game::getCpu() const {
    return this->cpu;
}

// Getter: Returns the Camden AI.
Camden* Game::getCamden() const {
    return this->camden;
}

// Getter: Returns the current turn (which player should play).
PlayerType Game::getTurn() const {
    return this->turn;
}

// Setter: Sets the human player.
void Game::setHuman(Player* the_human) {
    this->human = the_human;
}

// Setter: Sets the CPU player.
void Game::setCpu(Player* the_cpu) {
    this->cpu = the_cpu;
}

// Setter: Sets the Camden AI.
void Game::setCamden(Camden* new_camden) {
    this->camden = new_camden;
}

// Setter: Sets the current turn.
void Game::setTurn(PlayerType the_turn) {
    this->turn = the_turn;
}

// Method: Checks if any player has won the game.
bool Game::someoneHasWon() const {
    return this->human->allShipsAreSunk() || this->cpu->allShipsAreSunk(); // Returns true if either player's ships are all sunk.
}

// Method: Determines the winner of the game.
PlayerType Game::winner() const {
    if(this->someoneHasWon()) { // Check if the game has a winner.
        if(this->human->allShipsAreSunk()) // Check if human player lost.
            return CPU; // CPU wins.
        else
            return MAN; // Human wins.
    }
    throw logic_error("Nobody has won yet."); // Throw exception if called before game is over.
}

// Method: Switches the current turn between the human and CPU.
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

// Method: Executes the CPU's turn using Camden's move logic.
void Game::doCpuTurn(int(*rand_func)()) const {
    string camden_space = this->camden->makeMove(rand_func); // Get Camden's move.
    cout << camden_space << endl; // Print the chosen space.
    if (!(this->cpu->target(camden_space))) // Check if the move was valid.
        throw logic_error("Whoops! Something went wrong. (Camden\'s choice: " + camden_space + ")"); // Throw error if invalid.
}

// Method: Executes the human's turn.
void Game::doHumanTurn() const {
    this->human->doTurn(); // Call method for human player to take a turn.
}

// Method: Executes a turn for either the human or CPU, based on the current turn state.
void Game::doTurn(int(*rand_func)()) {
    if(this->turn == CPU)
        this->doCpuTurn(rand_func); // Call CPU's turn method.
    else if(this->turn == MAN)
        this->doHumanTurn(); // Call human's turn method.
    else
        throw logic_error("It is nobody\'s turn."); // Throw error if no valid turn state.
    this->switchTurn(); // Switch the turn after the current move.
}

// Method: Sets up the game by allowing the human to set their ships and the CPU to auto-set ships.
void Game::doSetUp(int(*rand_func)()) {
    this->human->askToSetShips(rand_func); // Prompt human to set their ships.
    cout << "\nCamden is setting his ships...";
    this->cpu->autoSetShips(rand_func); // CPU sets its ships automatically.
    sleep(1); // Wait for a moment to simulate setup time.
    cout << "   Done." << endl; // Indicate completion.
}

// Method: Performs a coin toss to decide which player goes first.
void Game::doCoinToss(int(*rand_func)()) {
    char user_coin_choice;
    cout << "" << endl;
    cout << "Coin toss! Winner goes first. Heads or Tails?" << endl;
    cout << "(H / h or T / t) > ";
    cin >> user_coin_choice; // Get user's choice.
    int coin_toss = rand_func() % 2; // Simulate coin toss (0 or 1).
    if (!coin_toss) { // If result is 0 (Heads).
        if(user_coin_choice == 'H' || user_coin_choice == 'h') {
            cout << "It\'s Heads, you won the toss and will go first." << endl;
            this->turn = MAN; // Set turn to human.
        } else {
            cout << "It\'s Heads, you lost the toss and will go second." << endl;
            this->turn = CPU; // Set turn to CPU.
        }
    } else { // If result is 1 (Tails).
        if(user_coin_choice == 'T' || user_coin_choice == 't') {
            cout << "It\'s Tails, you won the toss and will go first." << endl;
            this->turn = MAN; // Set turn to human.
        } else {
            cout << "It\'s Tails, you lost the toss and will go second." << endl;
            this->turn = CPU; // Set turn to CPU.
        }
    }
    sleep(1); // Wait for a moment to simulate delay.
    cout << "" << endl;
    cout << "Loading Game..." << endl;
    sleep(1); // Wait for another moment to simulate loading.
    cout << "" << endl;
}

// Method: Main game loop that continues until someone wins.
void Game::playGame(int(*rand_func)()) {
    do {
        cout << "" << endl;
        this->doTurn(rand_func); // Execute a turn.
        sleep(1); // Wait to simulate processing time.
        cout << "" << endl;
    } while (!(this->someoneHasWon())); // Continue until someone wins.
    if(this->someoneHasWon()) { // Check if a player has won.
        cout << "" << endl;
        if(this->winner() == CPU) { // Check if the CPU won.
            cout << "Camden wins!" << endl;
            sleep(1);
            cout << "" << endl;
            cout << "Here is Camden\'s grid: " << endl; // Show Camden's grid for reference.
            cout << "" << endl;
            this->cpu->getGrid()->showGrid(true); // Display the grid.
        }
    } else {
        cout << "You win!" << endl; // Print message if human wins.
    }
}
