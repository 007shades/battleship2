/* A Stud is a section of a Ship. Think of Studs as the holes in the plastic ships 
   in the real-life game of Battleship. Once all the Studs on a Ship have been hit, 
   the Ship will sink. */

#ifndef STUD_H
#define STUD_H

// ** Includes Required Classes and Enums **
#include "Enums.h"         // Includes enums such as StudName, SpaceName, ShipType, etc.
#include "GridSpace.h"     // Declares the GridSpace class (forward declared here).

// ** Forward Declarations **
class GridSpace;           // Forward declaration to resolve circular dependency.
class Ship;                // Forward declaration for the same reason.

// ** Declaration of the Stud Class **
class Stud {
    private:
        // ** Data Members **
        StudName studName;          // Enum representing the unique name of the stud.
        SpaceName onSpace;          // Enum representing the grid space where the stud is located.
        ShipType forShip;           // Enum representing the type of ship the stud belongs to.
        PlayerType ofPlayer;        // Enum representing the owner of the stud (MAN or CPU).
        StudStatus status {INTACT}; // Current status of the stud (INTACT or COMPROMISED).
        GridSpace* gridspace {nullptr}; // Pointer to the grid space this stud occupies.
        Ship* ofShip {nullptr};     // Pointer to the ship this stud belongs to.
        char label;                 // Character label used to represent the stud on the grid.

        // ** Private Helper Method **
        // Sets the type of the ship and assigns a label based on the stud's name.
        void set_ship_type(StudName stud_name);

    public:
        // ** Constructors and Destructor **
        Stud();                                         // Default constructor.
        explicit Stud(StudName stud_name);              // Initialize stud with a name.
        Stud(StudName stud_name, GridSpace* grid_space); // Initialize with name and grid space.
        Stud(StudName stud_name, PlayerType of_player);  // Initialize with name and owner.
        Stud(StudName stud_name, GridSpace* grid_space, StudStatus the_status); // With name, grid space, and status.
        Stud(StudName stud_name, PlayerType of_player, StudStatus the_status);  // With name, owner, and status.
        Stud(StudName stud_name, PlayerType of_player, Ship* of_ship);          // With name, owner, and ship.
        ~Stud();                                       // Destructor.

        // ** Getters (Accessors) **
        StudName getStudName() const;      // Returns the stud's name.
        SpaceName getOnSpace() const;      // Returns the space the stud is on.
        ShipType getForShip() const;       // Returns the ship type associated with the stud.
        PlayerType getOfPlayer() const;    // Returns the owner of the stud.
        StudStatus getStatus() const;      // Returns the status of the stud (INTACT or COMPROMISED).
        Ship* getOfShip() const;           // Returns the ship the stud belongs to.
        char getLabel() const;             // Returns the label of the stud.

        // ** Setters (Mutators) **
        void setStudName(StudName stud_name);     // Sets the name of the stud.
        void setOnSpace(SpaceName on_space);      // Sets the space the stud is on.
        void setOfPlayer(PlayerType for_player);  // Sets the owner of the stud.
        void setStatus(StudStatus stud_status);   // Sets the stud's status.
        void setOfShip(Ship* of_ship);            // Sets the ship the stud belongs to.
        void setLabel(char stud_label);           // Sets the label of the stud.

        // ** Status Check and Interaction **
        bool wasHit() const;      // Checks if the stud was hit (status is COMPROMISED).
        void hit();               // Marks the stud as hit, updates its label, and notifies the ship.
};

#endif
