#ifndef SUBMARINE_H
#define SUBMARINE_H

// ** Include Dependencies **
#include "Enums.h"     // For enumerations like PlayerType, StudName, ShipType, etc.
#include "Stud.h"      // For the definition of `Stud`, which represents the submarine's sections.
#include "Grid.h"      // For managing the grid and ship placement.
#include "Ship.h"      // The base class for `Submarine`.

#include <string>
    using std::string;

#include <array>
    using std::array;

// ** Class Definition **
class Submarine : public Ship {
    private:
        // ** Data Members **
        array<Stud*, 3> studs; // Fixed array of 3 studs, representing the submarine's sections.

    public:
        // ** Constructors and Destructor **
        Submarine();                                    // Default constructor.
        explicit Submarine(PlayerType of_player);       // Initialize with the owner type (CPU or MAN).
        explicit Submarine(Grid* on_grid);              // Initialize and associate with a grid.
        Submarine(Grid* on_grid, string start_space, char direction); // Initialize and place on the grid.
        ~Submarine();                                   // Destructor to clean up dynamically allocated studs.

        // ** Accessors **
        array<Stud*, 3> getStuds() const;               // Get the array of submarine's studs.
        Stud* getStud(StudName stud_name) const;        // Get a specific stud by its name.

        // ** Check and Interaction **
        bool hasStud(Stud* stud) const override;        // Check if a stud belongs to the submarine.
        
        // ** Stud Initialization and Grid Placement **
        void setStuds() override;                       // Initialize the submarine's studs.
        bool placeOnGrid(string start_space, char direction, bool print_out = false) const override;
        // Place the submarine on the grid.
};

#endif
