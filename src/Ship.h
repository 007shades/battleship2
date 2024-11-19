#ifndef SHIP_H
#define SHIP_H

// ** Includes Required Libraries and Classes **
#include "Enums.h"  // Enum definitions (e.g., ShipType, ShipStatus, PlayerType).
#include "Grid.h"   // Grid class for managing ship placement.
#include "Stud.h"   // Stud class represents ship sections.

#include <vector>   // Used for dynamic collections of `Stud` objects.
    using std::vector;
#include <string>   // Used for ship names.
    using std::string;

// Forward declaration of Stud class to resolve circular dependency.
class Stud;

// ** Ship Class Declaration **
class Ship {
    protected:
        PlayerType ofPlayer;            // Owner of the ship (MAN or CPU).
        Grid* onGrid {nullptr};         // Pointer to the grid where the ship is placed.
        vector<Stud*> intactStuds;      // List of intact studs (undamaged sections of the ship).
        vector<Stud*> destroyedStuds;   // List of destroyed studs (damaged sections of the ship).
        ShipType shipType;              // Type of the ship (CARRIER, BATTLESHIP, etc.).
        string shipName;                // Name of the ship (e.g., "Carrier").
        ShipStatus status {AFLOAT};     // Status of the ship (AFLOAT or SUNKEN).
        bool isOnGrid {false};          // Indicates whether the ship is placed on the grid.
        bool isReady {false};           // Indicates whether the ship is fully set up.

        // ** Private Helper Method **
        // Sets the name of the ship based on its type.
        void set_ship_name(ShipType ship_type);

    public:
        // ** Constructors and Destructor **
        Ship();                          // Default constructor.
        explicit Ship(ShipType ship_type); // Initialize the ship with its type.
        Ship(ShipType ship_type, PlayerType of_player); // Initialize with type and owner.
        Ship(ShipType ship_type, Grid* on_grid); // Initialize with type and grid.
        virtual ~Ship();                 // Virtual destructor for safe cleanup.

        // ** Getters **
        PlayerType getOfPlayer() const;  // Returns the owner of the ship.
        Grid* getOnGrid() const;         // Returns the grid the ship is placed on.
        vector<Stud*> getIntactSutds() const; // Returns the list of intact studs.
        vector<Stud*> getDestroyedStuds() const; // Returns the list of destroyed studs.
        ShipType getShipType() const;    // Returns the type of the ship.
        string getShipName() const;      // Returns the name of the ship.
        ShipStatus getShipStatus() const; // Returns the ship's status (AFLOAT/SUNKEN).
        bool getIsOnGrid() const;        // Returns whether the ship is on the grid.
        bool getIsReady() const;         // Returns whether the ship is ready for play.

        // ** Setters **
        void setOfPlayer(PlayerType of_player); // Sets the owner of the ship.
        void setGrid(Grid* on_grid);           // Sets the grid for the ship.
        void setShipType(ShipType ship_type);  // Sets the ship type and updates its name.
        void setShipStatus(ShipStatus ship_status); // Updates the ship's status.
        void setIsOnGrid(bool is_on_grid);     // Updates whether the ship is on the grid.
        void setIsReady(bool is_ready);        // Updates whether the ship is ready for play.

        // ** Stud Management **
        bool studIsIntact(Stud* stud) const;   // Checks if a specific stud is intact.
        bool wasSunk() const;                 // Checks if the ship has been sunk.
        void destroyStud(Stud* stud);         // Marks a specific stud as destroyed.

        // ** Pure Virtual Methods (To Be Implemented by Derived Classes) **
        virtual void setStuds() = 0;          // Initializes the ship's studs.
        virtual bool hasStud(Stud* stud) const = 0; // Checks if a ship owns a specific stud.
        virtual bool placeOnGrid(string start_space, char direction, bool print_out = true) const = 0; 
        // Places the ship on the grid.

};

#endif
