#ifndef DESTROYER_H
#define DESTROYER_H

// Ensures the header file is included only once during compilation.
#include "Enums.h"  // Includes enumerations for ShipType, PlayerType, etc.
#include "Stud.h"   // Includes the Stud class, representing parts of the ship.
#include "Grid.h"   // Includes the Grid class for managing the game board.

#include <string>   // Provides the string class.
    using std::string;

#include <array>    // Provides the array container class.
    using std::array;

#include "Ship.h"   // Includes the base Ship class.

// Destroyer class inherits from the Ship class.
class Destroyer : public Ship {
    private:
        array<Stud*, 3> studs; // Array to store pointers to 3 Stud objects.

    public:
        Destroyer();                               // Default constructor.
        explicit Destroyer(PlayerType of_player); // Constructor to initialize the Destroyer for a specific player.
        explicit Destroyer(Grid* on_grid);        // Constructor to place the Destroyer on a grid.
        Destroyer(Grid* on_grid, string start_space, char direction); 
        // Constructor to initialize and place the Destroyer on the grid.

        ~Destroyer();                              // Destructor to clean up dynamically allocated Stud objects.

        array<Stud*, 3> getStuds() const;         // Getter for the array of Stud pointers.
        Stud* getStud(StudName stud_name) const;  // Retrieves a specific Stud by its name.
        bool hasStud(Stud* stud) const override;  // Checks if a specific Stud is part of the Destroyer.
        void setStuds() override;                 // Initializes the Stud array.
        bool placeOnGrid(string start_space, char direction, bool print_out = true) const override; 
        // Attempts to place the Destroyer on the grid at a specific start space and direction.
};

#endif // Ends the include guard.
