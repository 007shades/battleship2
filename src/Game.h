#ifndef GAME_H
#define GAME_H

#include "Enums.h"   // Includes necessary enumerations (e.g., PlayerType).
#include "Player.h"  // Defines the Player class for human and CPU.
#include "Camden.h"  // Defines the AI logic for the CPU.

#include <string>
    using std::string;

// **Game Class**
// Represents the Battleship game, managing players, turns, and the main game flow.
class Game {
    private:
        Player* human {nullptr};   // Pointer to the human player.
        Player* cpu {nullptr};     // Pointer to the CPU player.
        Camden* camden {nullptr};  // AI logic for the CPU player.
        PlayerType turn;           // Indicates whose turn it is (MAN or CPU).

    public:
        // **Constructors and Destructor**
        Game();                               // Default constructor.
        explicit Game(string human_name);     // Constructor to initialize players with a human's name.
        Game(string human_name, int(*rand_func)()); // Full constructor that sets up and starts the game.
        ~Game();                              // Destructor to clean up dynamically allocated memory.

        // **Getter Methods**
        Player* getHuman() const;             // Returns a pointer to the human player.
        Player* getCpu() const;               // Returns a pointer to the CPU player.
        Camden* getCamden() const;            // Returns a pointer to the AI logic.
        PlayerType getTurn() const;           // Returns the current player's turn.

        // **Setter Methods**
        void setHuman(Player* the_human);     // Sets the human player.
        void setCpu(Player* the_cpu);         // Sets the CPU player.
        void setCamden(Camden* new_camden);   // Sets the AI logic.
        void setTurn(PlayerType turn);        // Sets the current turn.

        // **Game State Checks**
        bool someoneHasWon() const;           // Checks if any player has won the game.
        PlayerType winner() const;            // Returns the winner (throws an error if the game is not over).

        // **Game Flow Methods**
        void switchTurn();                    // Switches the turn between the human and CPU players.
        void doCpuTurn(int(*rand_func)()) const;  // Executes the CPU's turn using AI logic.
        void doHumanTurn() const;             // Executes the human player's turn.
        void doTurn(int(*rand_func)());       // Executes a turn for the current player.

        // **Setup Methods**
        void doSetUp(int(*rand_func)());      // Sets up the game by placing ships for both players.
        void doCoinToss(int(*rand_func)());   // Simulates a coin toss to decide who goes first.
        void doFinalSetup();                  // Finalizes setup by linking players and initializing AI.

        // **Main Game Loop**
        void playGame(int(*rand_func)());     // Main game loop that alternates turns until a winner is determined.
};

#endif
