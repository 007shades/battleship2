#ifndef GAME_H
#define GAME_H

#include "Enums.h"    // Includes enumerations for PlayerType and other game-related enums.
#include "Player.h"   // Includes the Player class.
#include "Camden.h"   // Includes the Camden AI class.

#include <string>     // Provides the string class.
    using std::string;

// ** Game Class **

// Manages the core game logic, including players, turns, and game progression.
class Game {
    private:
        Player* human {nullptr};   // Pointer to the human player.
        Player* cpu {nullptr};     // Pointer to the CPU player.
        Camden* camden {nullptr};  // Pointer to the Camden AI.
        PlayerType turn;           // Tracks whose turn it is (human or CPU).

    public:
        // ** Constructors and Destructor **
        Game();                                   // Default constructor.
        explicit Game(string human_name);         // Constructor with human player initialization.
        Game(string human_name, int(*rand_func)()); // Constructor with full game setup and gameplay.
        ~Game();                                  // Destructor to clean up dynamically allocated memory.

        // ** Getters **
        Player* getHuman() const;                 // Returns the human player.
        Player* getCpu() const;                   // Returns the CPU player.
        Camden* getCamden() const;                // Returns the Camden AI instance.
        PlayerType getTurn() const;               // Returns whose turn it is.

        // ** Setters **
        void setHuman(Player* the_human);         // Sets the human player.
        void setCpu(Player* the_cpu);             // Sets the CPU player.
        void setCamden(Camden* new_camden);       // Sets the Camden AI instance.
        void setTurn(PlayerType turn);            // Sets whose turn it is.

        // ** Game Status **
        bool someoneHasWon() const;               // Checks if someone has won the game.
        PlayerType winner() const;                // Determines the winner of the game.

        // ** Gameplay Logic **
        void switchTurn();                        // Switches the turn to the other player.
        void doCpuTurn(int(*rand_func)()) const;  // Executes the CPU's turn.
        void doHumanTurn() const;                 // Executes the human player's turn.
        void doTurn(int(*rand_func)());           // Executes a turn for the current player.

        // ** Setup Functions **
        void doSetUp(int(*rand_func)());          // Handles setup for ship placement.
        void doCoinToss(int(*rand_func)());       // Simulates a coin toss to determine turn order.
        void doFinalSetup();                      // Finalizes setup (assigns foes and initializes AI).

        // ** Game Loop **
        void playGame(int(*rand_func)());         // Runs the main game loop.
};

#endif
