#ifndef SHIP_H // Include guard to prevent multiple inclusions.
#define SHIP_H

#include "Enums.h" // Include for enumerated types used in the class.
#include "Grid.h" // Include for the Grid class.
#include "Stud.h" // Include for the Stud class.

#include <vector> // Include for using vector class.
    using std::vector; // Use vector from the standard namespace.

#include <string> // Include for using string class.
    using std::string; // Use string from the standard namespace.

class Stud; // Forward declaration of Stud class to avoid circular dependency.

// Declaration of the Ship class representing a ship in the game.
class Ship {
    protected:
        PlayerType ofPlayer; // The player type (CPU or human) that owns the ship.
        Grid* onGrid {nullptr}; // Pointer to the grid where the ship is placed.
        vector<Stud*> intactStuds; // Vector of intact studs representing undamaged parts of the ship.
        vector<Stud*> destroyedStuds; // Vector of destroyed studs representing damaged parts of the ship.
        ShipType shipType; // The type of the ship (e.g., Carrier, Battleship).
        string shipName; // The name of the ship (e.g., "Carrier").
        ShipStatus status {AFLOAT}; // The status of the ship (AFLOAT or SUNKEN).
        bool isOnGrid {false}; // Flag indicating if the ship is placed on the grid.
        bool isReady {false}; // Flag indicating if the ship is set and ready to play.

        // Method to set the ship's name based on its type.
        void set_ship_name(ShipType ship_type);

    public:
        // Constructors and Destructor.
        Ship(); // Default constructor.
        explicit Ship(ShipType ship_type); // Constructor initializing the ship type.
        Ship(ShipType ship_type, PlayerType of_player); // Constructor with ship type and player type.
        Ship(ShipType ship_type, Grid* on_grid); // Constructor with ship type and grid.
        ~Ship(); // Destructor to clean up resources.

        // Getter methods.
        PlayerType getOfPlayer() const; // Returns the player type owning the ship.
        Grid* getOnGrid() const; // Returns the grid the ship is on.
        vector<Stud*> getIntactSutds() const; // Returns a vector of intact studs.
        vector<Stud*> getDestroyedStuds() const; // Returns a vector of destroyed studs.
        ShipType getShipType() const; // Returns the type of the ship.
        string getShipName() const; // Returns the name of the ship.
        ShipStatus getShipStatus() const; // Returns the status of the ship.
        bool getIsOnGrid() const; // Returns whether the ship is placed on the grid.
        bool getIsReady() const; // Returns whether the ship is ready to play.

        // Setter methods.
        void setOfPlayer(PlayerType of_player); // Sets the player type owning the ship.
        void setGrid(Grid* on_grid); // Sets the grid the ship is on.
        void setShipType(ShipType ship_type); // Sets the type of the ship.
        void setShipStatus(ShipStatus ship_status); // Sets the status of the ship.
        void setIsOnGrid(bool is_on_grid); // Sets whether the ship is placed on the grid.
        void setIsReady(bool is_ready); // Sets whether the ship is ready to play.

        // Methods to check and update ship status.
        bool studIsIntact(Stud* stud) const; // Checks if a specific stud on the ship is intact.
        bool wasSunk() const; // Checks if the ship has been sunk (all studs destroyed).

        // Pure virtual methods to be implemented by derived classes.
        virtual void setStuds() = 0; // Method to set studs on the ship.
        virtual bool hasStud(Stud* stud) const = 0; // Checks if the ship has a specific stud.
        virtual bool placeOnGrid(string start_space, char direction, bool print_out = true) const = 0; // Places the ship on the grid.

        // Method to mark a stud as destroyed.
        void destroyStud(Stud* stud);
};

#endif // End of include guard.
