#ifndef BATTLESHIP_H
#define BATTLESHIP_H

// Ensures the header file is included only once during compilation.
#include "Enums.h"  // Includes enumerations used in the class.
#include "Stud.h"   // Includes the Stud class for ship components.
#include "Grid.h"   // Includes the Grid class for managing the game board.

#include <string>   // Provides the string class.
    using std::string;

#include <array>    // Provides the array container class.
    using std::array;

#include "Ship.h"   // Includes the base Ship class.

// Battleship class inherits from the Ship class.
class Battleship : public Ship {
    private:
        array<Stud*, 4> studs; // Array to store pointers to Stud objects (specific to this ship).

    public:
        Battleship(); // Default constructor.
        explicit Battleship(PlayerType of_player); // Constructor to initialize the ship for a specific player.
        explicit Battleship(Grid* on_grid); // Constructor to place the ship on a grid.
        Battleship(Grid* on_grid, string start_space, char direction); // Constructor to initialize and place the ship.
        ~Battleship(); // Destructor to clean up dynamically allocated Stud objects.

        array<Stud*, 4> getStuds() const; // Getter for the array of Stud pointers.
        Stud* getStud(StudName stud_name) const; // Retrieves a specific Stud by its name.
        bool hasStud(Stud* stud) const override; // Checks if a specific Stud is part of the ship.
        void setStuds() override; // Initializes the Stud array.
        bool placeOnGrid(string start_space, char direction, bool print_out = true) const override; 
        // Attempts to place the ship on the grid at a specific start space and direction.
};

#endif // Ends the include guard.
