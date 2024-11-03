#ifndef SUBMARINE_H // Include guard to prevent multiple inclusions.
#define SUBMARINE_H

#include "Enums.h" // Include for enumerated types used in the class.
#include "Stud.h" // Include for the Stud class.
#include "Grid.h" // Include for the Grid class.

#include <string> // Include for using string.
    using std::string; // Use string from the standard namespace.

#include <array> // Include for using array.
    using std::array; // Use array from the standard namespace.

#include "Ship.h" // Include for the base Ship class.

// Declaration of the Submarine class, which inherits from Ship.
class Submarine : public Ship {
    private:
        array<Stud*, 3> studs; // Array of pointers to Studs representing sections of the Submarine.

    public:
        // Constructors and Destructor.
        Submarine(); // Default constructor.
        explicit Submarine(PlayerType of_player); // Constructor initializing the Submarine with a PlayerType.
        explicit Submarine(Grid* on_grid); // Constructor initializing the Submarine with a Grid.
        Submarine(Grid* on_grid, string start_space, char direction); // Constructor initializing the Submarine with a Grid, start space, and direction.
        ~Submarine(); // Destructor to clean up resources.

        // Getter methods.
        array<Stud*, 3> getStuds() const; // Returns an array of pointers to the Submarine's Studs.
        Stud* getStud(StudName stud_name) const; // Returns a pointer to a specific Stud by its name.

        // Method to check if the Submarine has a specific Stud.
        bool hasStud(Stud* stud) const override;

        // Method to set the Submarine's Studs.
        void setStuds() override;

        // Method to place the Submarine on the grid.
        bool placeOnGrid(string start_space, char direction, bool print_out = false) const override;
};

#endif // End of include guard.
