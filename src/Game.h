#ifndef GAME_H // Include guard to prevent multiple inclusions.
#define GAME_H

#include "Enums.h" // Include for enumerated types used in the class.
#include "Player.h" // Include for Player class to handle player functionality.
#include "Camden.h" // Include for Camden AI class.

#include <string> // Include for using the string class.
    using std::string; // Use string from the standard namespace.

// Declaration of the Game class.
class Game {
    private:
        Player* human {nullptr}; // Pointer to the human player.
        Player* cpu {nullptr}; // Pointer to the CPU player.
        Camden* camden {nullptr}; // Pointer to the Camden AI instance.
        PlayerType turn; // Variable to track whose turn it is.

    public:
        // Constructors and Destructor.
        Game(); // Default constructor.
        explicit Game(string human_name); // Constructor initializing the game with a human player name.
        Game(string human_name, int(*rand_func)()); // Constructor initializing and starting the game with setup.
        ~Game(); // Destructor to clean up dynamically allocated resources.

        // Getter methods.
        Player* getHuman() const; // Returns the human player.
        Player* getCpu() const; // Returns the CPU player.
        Camden* getCamden() const; // Returns the Camden AI instance.
        PlayerType getTurn() const; // Returns whose turn it currently is.

        // Setter methods.
        void setHuman(Player* the_human); // Sets the human player.
        void setCpu(Player* the_cpu); // Sets the CPU player.
        void setCamden(Camden* new_camden); // Sets the Camden AI instance.
        void setTurn(PlayerType turn); // Sets whose turn it is.

        // Game status methods.
        bool someoneHasWon() const; // Checks if any player has won the game.
        PlayerType winner() const; // Determines the winner of the game.

        // Game control methods.
        void switchTurn(); // Switches the current turn between players.
        void doCpuTurn(int(*rand_func)()) const; // Executes the CPU's turn.
        void doHumanTurn() const; // Executes the human's turn.
        void doTurn(int(*rand_func)()); // Executes a turn based on whose turn it is.

        // Game setup and gameplay methods.
        void doSetUp(int(*rand_func)()); // Sets up the game by initializing ships for both players.
        void doCoinToss(int(*rand_func)()); // Performs a coin toss to decide who goes first.
        void playGame(int(*rand_func)()); // Main game loop that continues until someone wins.
};

#endif // End of include guard.
