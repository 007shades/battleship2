#ifndef CARRIER_H // Include guard to prevent multiple inclusions.
#define CARRIER_H

#include "Enums.h" // Include for enumerated types used in the class.
#include "Stud.h" // Include for the Stud class, representing parts of the ship.
#include "Grid.h" // Include for the Grid class, used for ship placement on the grid.

#include <string> // Include for using the string class.
    using std::string; // Use string from the standard namespace.

#include <array> // Include for using the array class.
    using std::array; // Use array from the standard namespace.

#include "Ship.h" // Include the base Ship class to inherit from.

// Declaration of the Carrier class, derived from Ship.
class Carrier : public Ship {
    private:
        array<Stud*, 5> studs; // Array to store pointers to the individual parts (studs) of the carrier.
    public:
        // Constructors and Destructor.
        Carrier(); // Default constructor.
        explicit Carrier(PlayerType of_player); // Constructor taking a player type.
        explicit Carrier(Grid* on_grid); // Constructor taking a grid pointer.
        Carrier(Grid* on_grid, string start_space, char direction); // Constructor with grid and placement details.
        ~Carrier(); // Destructor to clean up dynamically allocated resources.

        // Getter methods.
        array<Stud*, 5> getStuds() const; // Returns the array of studs.
        Stud* getStud(StudName stud_name) const; // Returns a specific stud by name.

        // Override methods from the base class.
        bool hasStud(Stud* stud) const override; // Checks if a given stud is part of the carrier.
        void setStuds() override; // Initializes the studs of the carrier.
        bool placeOnGrid(string start_space, char direction, bool print_out = true) const override; // Places the carrier on the grid.
};

#endif // End of include guard.
