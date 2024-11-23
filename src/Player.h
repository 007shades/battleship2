#ifndef PLAYER_H
#define PLAYER_H

// Required includes for various components of the Player class.
#include "Enums.h"
#include "Ship.h"
#include "Grid.h"
#include "Carrier.h"
#include "Battleship.h"
#include "Destroyer.h"
#include "Submarine.h"
#include "Cruiser.h"

#include <array>      // For fixed-size arrays.
    using std::array;
#include <vector>     // For dynamic arrays.
    using std::vector;
#include <string>     // For string handling.
    using std::string;

// The Player class represents a player in the game, either human or CPU.
class Player {
    private:
        // Private member variables to store the state and attributes of the player.
        PlayerType type;                     // Type of the player: MAN (human) or CPU.
        string name;                         // Name of the player.
        Grid* grid {nullptr};                // Grid representing the player's board.
        Player* foe {nullptr};               // Pointer to the opponent player.
        Grid* foeGrid {nullptr};             // Grid representing the opponent's board.
        array<Ship*, 5> ships;               // Array of pointers to the player's ships.
        vector<Ship*> floatingShips;         // Ships that are still floating (not sunk).
        vector<Ship*> sunkenShips;           // Ships that have been sunk.
        vector<string> targetedSpaces;       // List of spaces that the player has targeted.
        vector<string> hitSpaces;            // List of spaces where the player scored a hit.
        vector<string> missSpaces;           // List of spaces where the player missed.
        vector<char> HMHist;                 // History of hits ('H') and misses ('M').

    public:
        // Constructors
        Player();                                        // Default constructor.
        explicit Player(PlayerType player_type);         // Constructor with player type.
        Player(PlayerType player_type, string player_name); // Constructor with type and name.
        Player(PlayerType player_type, string player_name, Player* the_foe); // Constructor with type, name, and foe.

        // Destructor
        ~Player();                                       // Cleans up resources.

        // Getter Methods
        PlayerType getPlayerType() const;               // Gets the player type.
        string getName() const;                         // Gets the player's name.
        Grid* getGrid()&;                               // Gets the player's grid.
        Player* getFoe() const;                         // Gets the pointer to the opponent player.
        Grid* getFoeGrid()&;                            // Gets the grid of the opponent player.
        array<Ship*, 5> getShips() const;               // Gets the array of player's ships.
        vector<Ship*> getFloatingShips() const;         // Gets the list of floating ships.
        vector<Ship*> getSunkenShips() const;           // Gets the list of sunken ships.
        vector<string> getTargetedSpaces() const;       // Gets the list of targeted spaces.
        vector<string> getHitSpaces() const;            // Gets the list of hit spaces.
        vector<string> getMissSpaces() const;           // Gets the list of missed spaces.
        vector<char> getHMHist() const;                 // Gets the hit/miss history.

        // Setter Methods
        void setPlayerType(PlayerType player_type);     // Sets the player type.
        void setName(string name);                      // Sets the player's name.
        void setFoe(Player* the_foe);                   // Sets the opponent player.
        void setFoeGrid(Grid* the_grid);                // Sets the opponent's grid.

        // Gameplay Interaction
        void makeFoe(Player* &the_foe);                 // Links the opponent player and their grid.

        // Ship State Checking
        bool hasShip(Ship* ship) const;                 // Checks if a ship belongs to the player.
        bool shipIsFloating(Ship* ship) const;          // Checks if a ship is still floating.
        bool shipIsSunken(Ship* ship) const;            // Checks if a ship is sunken.

        // Display Information
        void stillFloating() const;                    // Displays the player's floating ships.
        void notSunkYet() const;                       // Displays the opponent's floating ships.
        void showFoe() const;                          // Displays the opponent's grid.
        void showOwn() const;                          // Displays the player's grid.

        // Gameplay State
        Ship* justSunkenShip() const;                  // Gets the most recently sunken ship.
        void sinkShip(Ship* ship);                     // Marks a ship as sunk.

        // Targeting Methods
        bool spaceWasTargeted(string space) const;     // Checks if a space has been targeted.
        bool target(string space, bool do_cout = true);// Targets a space during gameplay.
        bool processInput(string input);               // Processes input commands during gameplay.

        // Game Completion Check
        bool allShipsAreSunk() const;                  // Checks if all ships are sunk.

        // Ship Placement
        void setCarrier();                             // Manually places the Carrier ship.
        void setBattleship();                          // Manually places the Battleship ship.
        void setDestroyer();                           // Manually places the Destroyer ship.
        void setSubmarine();                           // Manually places the Submarine ship.
        void setCruiser();                             // Manually places the Cruiser ship.
        void manuallySetShips();                       // Allows manual placement of all ships.

        // Automatic Ship Placement
        void autoPutShip(Ship* ship, int(*rand_func)());// Automatically places a single ship.
        void autoSetShip(char ship_char, int(*rand_func)()); // Automatically places a specific ship type.
        void autoSetShips(int(*rand_func)());          // Automatically places all ships.

        // Turn Management
        void askToSetShips(int(*rand_func)());         // Prompts the player to set ships (manual or automatic).
        void doTurn();                                 // Executes the player's turn.
};

#endif
