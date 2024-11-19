#ifndef PLAYER_H
#define PLAYER_H

// ** Includes Required Libraries and Classes **
#include "Enums.h"         // Enum definitions (e.g., PlayerType, ShipType).
#include "Ship.h"          // Base class for different ships.
#include "Grid.h"          // Represents the player's grid.
#include "Carrier.h"       // Specific ship class definitions.
#include "Battleship.h"
#include "Destroyer.h"
#include "Submarine.h"
#include "Cruiser.h"

#include <array>           // Used for managing fixed-size arrays (ships).
    using std::array;
#include <vector>          // Used for dynamic collections (e.g., hit/miss spaces).
    using std::vector;
#include <string>          // Used for player names and coordinates.
    using std::string;

// ** Player Class **
// Represents a player in the game (human or CPU). Manages ships, targeting, and interactions.
class Player {
    private:
        PlayerType type;                   // Type of player (CPU or MAN).
        string name;                       // Player's name.
        Grid* grid {nullptr};              // Pointer to the player's grid.
        Player* foe {nullptr};             // Pointer to the player's opponent.
        Grid* foeGrid {nullptr};           // Pointer to the opponent's grid.
        array<Ship*, 5> ships;             // Array of the player's ships (Carrier, Battleship, etc.).
        vector<Ship*> floatingShips;       // List of ships still floating.
        vector<Ship*> sunkenShips;         // List of ships that have been sunk.
        vector<string> targetedSpaces;     // List of all targeted spaces.
        vector<string> hitSpaces;          // List of all spaces hit.
        vector<string> missSpaces;         // List of all spaces missed.
        vector<char> HMHist;               // History of hits ('H') and misses ('M').

    public:
        // ** Constructors and Destructor **
        Player();                          // Default constructor.
        explicit Player(PlayerType player_type); // Initialize player with type.
        Player(PlayerType player_type, string player_name); // Initialize with type and name.
        Player(PlayerType player_type, string player_name, Player* the_foe); // Initialize with type, name, and foe.
        ~Player();                         // Destructor for cleaning up resources.

        // ** Getters **
        PlayerType getPlayerType() const;  // Returns the player's type.
        string getName() const;            // Returns the player's name.
        Grid* getGrid() &;                 // Returns a reference to the player's grid.
        Player* getFoe() const;            // Returns a pointer to the player's foe.
        Grid* getFoeGrid() &;              // Returns a reference to the foe's grid.
        array<Ship*, 5> getShips() const;  // Returns the array of the player's ships.
        vector<Ship*> getFloatingShips() const; // Returns the list of floating ships.
        vector<Ship*> getSunkenShips() const;   // Returns the list of sunken ships.
        vector<string> getTargetedSpaces() const; // Returns the list of targeted spaces.
        vector<string> getHitSpaces() const;      // Returns the list of spaces hit.
        vector<string> getMissSpaces() const;     // Returns the list of spaces missed.
        vector<char> getHMHist() const;           // Returns the hit/miss history.

        // ** Setters **
        void setPlayerType(PlayerType player_type); // Sets the player's type.
        void setName(string name);                  // Sets the player's name.
        void setFoe(Player* the_foe);               // Sets the player's foe.
        void setFoeGrid(Grid* the_grid);            // Sets the player's foe's grid.

        // ** Foe Management **
        void makeFoe(Player* &the_foe);             // Links the player with their foe.

        // ** Ship Management **
        bool hasShip(Ship* ship) const;             // Checks if the player has a specific ship.
        bool shipIsFloating(Ship* ship) const;      // Checks if a specific ship is still floating.
        bool shipIsSunken(Ship* ship) const;        // Checks if a specific ship is sunk.

        // ** Display Functions **
        void stillFloating() const;                // Displays ships still floating.
        void notSunkYet() const;                   // Displays opponent's unsunk ships.
        void showFoe() const;                      // Displays the foe's grid.
        void showOwn() const;                      // Displays the player's grid.

        // ** Ship State Functions **
        Ship* justSunkenShip() const;              // Returns the most recently sunk ship.
        void sinkShip(Ship* ship);                 // Marks a ship as sunk.

        // ** Targeting Functions **
        bool spaceWasTargeted(string space) const; // Checks if a space was already targeted.
        bool target(string space, bool do_cout = true); // Targets a space on the foe's grid.
        bool processInput(string input);           // Processes input for commands or targeting.

        // ** Game State Functions **
        bool allShipsAreSunk() const;              // Checks if all player's ships are sunk.

        // ** Ship Placement Functions **
        void setCarrier();                         // Places the Carrier manually.
        void setBattleship();                      // Places the Battleship manually.
        void setDestroyer();                       // Places the Destroyer manually.
        void setSubmarine();                       // Places the Submarine manually.
        void setCruiser();                         // Places the Cruiser manually.
        void manuallySetShips();                   // Allows manual placement of all ships.

        void autoPutShip(Ship* ship, int(*rand_func)()); // Automatically places a specific ship.
        void autoSetShip(char ship_char, int(*rand_func)()); // Automatically places a ship by type.
        void autoSetShips(int(*rand_func)());              // Automatically places all ships.

        // ** Turn Management **
        void askToSetShips(int(*rand_func)());     // Asks if ships should be auto-set or manually set.
        void doTurn();                             // Handles the player's turn.
};

#endif
