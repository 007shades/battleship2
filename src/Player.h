#ifndef PLAYER_H // Include guard to prevent multiple inclusions.
#define PLAYER_H

#include "Enums.h" // Include for enumerated types used in the class.
#include "Ship.h" // Include for the Ship base class.
#include "Grid.h" // Include for the Grid class.
#include "Carrier.h" // Include for Carrier class.
#include "Battleship.h" // Include for Battleship class.
#include "Destroyer.h" // Include for Destroyer class.
#include "Submarine.h" // Include for Submarine class.
#include "Cruiser.h" // Include for Cruiser class.

#include <array> // Include for using array class.
    using std::array; // Use array from the standard namespace.
#include <vector> // Include for using vector class.
    using std::vector; // Use vector from the standard namespace.
#include <string> // Include for using string class.
    using std::string; // Use string from the standard namespace.

// Declaration of the Player class representing a game player.
class Player {
    private:
        PlayerType type; // The type of the player (e.g., CPU or MAN).
        string name; // The name of the player.
        Grid* grid {nullptr}; // Pointer to the player's grid.
        Player* foe {nullptr}; // Pointer to the opponent player.
        Grid* foeGrid {nullptr}; // Pointer to the opponent's grid.
        array<Ship*, 5> ships; // Array to store the player's ships.
        vector<Ship*> floatingShips; // Vector of ships that are still afloat.
        vector<Ship*> sunkenShips; // Vector of ships that have been sunk.
        vector<string> targetedSpaces; // Vector of spaces that have been targeted.
        vector<string> hitSpaces; // Vector of spaces where hits were recorded.
        vector<string> missSpaces; // Vector of spaces where misses were recorded.
        vector<char> HMHist; // Vector to keep a history of hits ('H') and misses ('M').

    public:
        // Constructors and Destructor.
        Player(); // Default constructor.
        explicit Player(PlayerType player_type); // Constructor initializing the player type.
        Player(PlayerType player_type, string player_name); // Constructor with player type and name.
        Player(PlayerType player_type, string player_name, Player* the_foe); // Constructor with player type, name, and foe.
        ~Player(); // Destructor to clean up dynamically allocated resources.

        // Getter methods.
        PlayerType getPlayerType() const; // Returns the type of the player.
        string getName() const; // Returns the name of the player.
        Grid* getGrid() const; // Returns the grid of the player.
        Player* getFoe() const; // Returns the player's opponent.
        Grid* getFoeGrid() const; // Returns the grid of the opponent.
        array<Ship*, 5> getShips() const; // Returns the array of ships owned by the player.
        vector<Ship*> getFloatingShips() const; // Returns the vector of floating ships.
        vector<Ship*> getSunkenShips() const; // Returns the vector of sunken ships.
        vector<string> getTargetedSpaces() const; // Returns the vector of targeted spaces.
        vector<string> getHitSpaces() const; // Returns the vector of hit spaces.
        vector<string> getMissSpaces() const; // Returns the vector of miss spaces.
        vector<char> getHMHist() const; // Returns the hit/miss history.

        // Setter methods.
        void setPlayerType(PlayerType player_type); // Sets the player type.
        void setName(string name); // Sets the name of the player.
        void setFoe(Player* the_foe); // Sets the player's opponent.
        void setFoeGrid(Grid* the_grid); // Sets the grid of the opponent.

        // Method to link the opponent and their grid.
        void makeFoe(Player* the_foe);

        // Methods to check the status of ships.
        bool hasShip(Ship* ship) const; // Checks if the player has a specific ship.
        bool shipIsFloating(Ship* ship) const; // Checks if a specific ship is floating.
        bool shipIsSunken(Ship* ship) const; // Checks if a specific ship is sunken.

        // Methods to display information about ships.
        void stillFloating() const; // Prints the names of ships that are still floating.
        void notSunkYet() const; // Prints the names of the opponent's ships that are still afloat.
        void showFoe() const; // Displays the opponent's grid.
        void showOwn() const; // Displays the player's own grid.

        // Method to check if a ship has just been sunk.
        Ship* justSunkenShip() const;

        // Method to update the status of a sunken ship.
        void sinkShip(Ship* ship);

        // Method to check if a space has been targeted.
        bool spaceWasTargeted(string space) const;
        
        // Method to target a space on the opponent's grid.
        bool target(string space);

        // Method to process user input for gameplay.
        bool processInput(string input);
        
        // Method to check if all ships are sunk.
        bool allShipsAreSunk() const;

        // Methods for manual ship placement.
        void setCarrier(); // Sets up the Carrier ship.
        void setBattleship(); // Sets up the Battleship ship.
        void setDestroyer(); // Sets up the Destroyer ship.
        void setSubmarine(); // Sets up the Submarine ship.
        void setCruiser(); // Sets up the Cruiser ship.
        void manuallySetShips(); // Sets up all ships manually.

        // Methods for automatic ship placement.
        void autoPutShip(Ship* ship, int(*rand_func)()); // Automatically places a ship on the grid.
        void autoSetShip(char ship_char, int(*rand_func)()); // Automatically sets a specific type of ship.
        void autoSetShips(int(*rand_func)()); // Automatically sets all ships.

        // Method to ask the player whether to auto-set or manually place ships.
        void askToSetShips(int(*rand_func)());

        // Method to execute the player's turn.
        void doTurn();
};

#endif // End of include guard.
