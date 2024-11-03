/* A Stud is a section of a Ship. Think of Studs as the holes in the plastic ships
in the real-life game of Battleship. Once all the Studs on a Ship have been hit,
the Ship will sink. */

#ifndef STUD_H // Include guard to prevent multiple inclusions.
#define STUD_H

#include "Enums.h" // Include for enumerated types used in the class.
#include "GridSpace.h" // Include for the GridSpace class.

class GridSpace; // Forward declaration of GridSpace to avoid circular dependency.
class Ship; // Forward declaration of Ship to avoid circular dependency.

// Declaration of the Stud class representing a section of a Ship.
class Stud {
    private:
        StudName studName; // The name of the Stud.
        SpaceName onSpace; // The space on the grid where the Stud is located.
        ShipType forShip; // The type of Ship the Stud belongs to (e.g., Carrier, Battleship).
        PlayerType ofPlayer; // The player type (CPU or human) that owns the Stud.
        StudStatus status {INTACT}; // The status of the Stud (INTACT or COMPROMISED).
        GridSpace* gridspace {nullptr}; // Pointer to the GridSpace the Stud is on.
        Ship* ofShip {nullptr}; // Pointer to the Ship the Stud is part of.
        char label; // Character label representing the Stud on the grid.

        // Method to set the type of ship the Stud belongs to based on its name.
        void set_ship_type(StudName stud_name);

    public:
        // Constructors and Destructor.
        Stud(); // Default constructor.
        explicit Stud(StudName stud_name); // Constructor initializing the Stud with a StudName.
        Stud(StudName stud_name, GridSpace* grid_space); // Constructor with StudName and GridSpace.
        Stud(StudName stud_name, PlayerType of_player); // Constructor with StudName and PlayerType.
        Stud(StudName stud_name, GridSpace* grid_space, StudStatus the_status); // Constructor with StudName, GridSpace, and StudStatus.
        Stud(StudName stud_name, PlayerType of_player, StudStatus the_status); // Constructor with StudName, PlayerType, and StudStatus.
        Stud(StudName stud_name, PlayerType of_player, Ship* of_ship); // Constructor with StudName, PlayerType, and Ship.
        ~Stud(); // Destructor to clean up resources.

        // Getter methods.
        StudName getStudName() const; // Returns the name of the Stud.
        SpaceName getOnSpace() const; // Returns the space the Stud is on.
        ShipType getForShip() const; // Returns the type of Ship the Stud belongs to.
        PlayerType getOfPlayer() const; // Returns the PlayerType that owns the Stud.
        StudStatus getStatus() const; // Returns the status of the Stud (INTACT or COMPROMISED).
        Ship* getOfShip() const; // Returns a pointer to the Ship the Stud is part of.
        char getLabel() const; // Returns the character label of the Stud.

        // Setter methods.
        void setStudName(StudName stud_name); // Sets the StudName and updates the type and label.
        void setOnSpace(SpaceName on_space); // Sets the space the Stud is on.
        void setOfPlayer(PlayerType for_player); // Sets the PlayerType that owns the Stud.
        void setStatus(StudStatus stud_status); // Sets the status of the Stud.
        void setOfShip(Ship* of_ship); // Sets the Ship the Stud is part of.
        void setLabel(char stud_label); // Sets the label of the Stud.

        // Methods to check and update the status of the Stud.
        bool wasHit() const; // Checks if the Stud was hit (status is COMPROMISED).
        void hit(); // Marks the Stud as hit, updates the label, and notifies the Ship.
};

#endif // End of include guard.
