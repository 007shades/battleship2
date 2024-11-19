#ifndef CARRIER_H
#define CARRIER_H

// Ensures the header file is included only once during compilation.
#include "Enums.h"  // Includes enumerations for ShipType, PlayerType, etc.
#include "Stud.h"   // Includes the Stud class, representing parts of the ship.
#include "Grid.h"   // Includes the Grid class, managing the game board.

#include <string>   // Provides the string class.
    using std::string;

#include <array>    // Provides the array container class.
    using std::array;

#include "Ship.h"   // Includes the base Ship class.

// Carrier class inherits from the Ship class.
class Carrier : public Ship {
    private:
        array<Stud*, 5> studs; // Array to store pointers to 5 Stud objects.

    public:
        Carrier();                               // Default constructor.
        explicit Carrier(PlayerType of_player); // Constructor to initialize the Carrier for a specific player.
        explicit Carrier(Grid* on_grid);        // Constructor to place the Carrier on a grid.
        Carrier(Grid* on_grid, string start_space, char direction); 
        // Constructor to initialize and place the Carrier on the grid.

        ~Carrier();                              // Destructor to clean up dynamically allocated Stud objects.

        array<Stud*, 5> getStuds() const;        // Getter for the array of Stud pointers.
        Stud* getStud(StudName stud_name) const; // Retrieves a specific Stud by its name.
        bool hasStud(Stud* stud) const override; // Checks if a specific Stud is part of the Carrier.
        void setStuds() override;                // Initializes the Stud array.
        bool placeOnGrid(string start_space, char direction, bool print_out = true) const override; 
        // Attempts to place the Carrier on the grid at a specific start space and direction.
};

#endif // Ends the include guard.
