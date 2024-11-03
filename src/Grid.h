#ifndef GRID_H // Include guard to prevent multiple inclusions.
#define GRID_H

#include <array> // Include for using array class.
    using std::array; // Use array from the standard namespace.

#include <string> // Include for using string class.
    using std::string; // Use string from the standard namespace.

#include <vector> // Include for using vector class.
    using std::vector; // Use vector from the standard namespace.

#include "Enums.h" // Include for enumerated types used in the class.
#include "GridSpace.h" // Include for the GridSpace class representing individual grid spaces.

// Declaration of the Grid class.
class Grid {
    private:
        array<GridSpace*, 100> grid; // Array to hold pointers to GridSpace objects, representing the game grid.
        PlayerType ofPlayer; // Player type associated with this grid (e.g., CPU or human).
        vector<SpaceName> noGoSpaces; // Vector of spaces marked as "no-go" for placement.

        // Private methods to initialize the grid.
        void populate_grid(); // Populates the grid with nullptr to initialize spaces.
        void populate_grid(PlayerType of_player); // Populates the grid with new GridSpace objects associated with a player.

    public:
        // Constructors and Destructor.
        Grid(); // Default constructor that initializes the grid with empty spaces.
        explicit Grid(PlayerType of_player); // Constructor that initializes the grid for a specific player.
        ~Grid(); // Destructor to clean up dynamically allocated GridSpace objects.

        // Getter methods.
        array<GridSpace*, 100> getGrid() const; // Returns the grid as an array of GridSpace pointers.
        PlayerType getOfPlayer() const; // Returns the player type associated with the grid.
        vector<SpaceName> getNoGoSpaces() const; // Returns the vector of "no-go" spaces.

        // Setter methods.
        void setGrid(array<GridSpace*, 100> the_grid); // Sets the grid with a given array of GridSpace pointers.
        void setOfPlayer(PlayerType of_player); // Sets the player type associated with the grid.

        // Methods to manage "no-go" spaces.
        void addNoGoSpace(SpaceName space); // Adds a single space to the "no-go" list.
        void addNoGoSpaces(vector<string> space_strings); // Adds multiple spaces to the "no-go" list.

        // Methods to retrieve GridSpace objects.
        GridSpace* getSpace(SpaceName space_name) const; // Returns a pointer to a GridSpace given its SpaceName.
        GridSpace* getSpace(string space_string) const; // Returns a pointer to a GridSpace given its string representation.
        GridSpace* getSpace(Column column, Row row) const; // Returns a pointer to a GridSpace given its column and row.
        GridSpace* getSpace(int column_number, int row_number) const; // Returns a pointer to a GridSpace given column and row numbers.

        // Methods to check for "no-go" spaces.
        bool isNoGoSpace(string space_string) const; // Checks if a space is in the "no-go" list using its string representation.
        bool isNoGoSpace(SpaceName space_name) const; // Checks if a space is in the "no-go" list using its SpaceName.
        bool hasNoGoSpace(vector<string> space_strings) const; // Checks if any given spaces are in the "no-go" list.

        // Static methods for navigating the grid.
        static string N(string start); // Gets the space string north of the given space.
        static string S(string start); // Gets the space string south of the given space.
        static string E(string start); // Gets the space string east of the given space.
        static string W(string start); // Gets the space string west of the given space.
        static string goDirection(string start, char direction); // Returns a new space string after moving in the specified direction.
        static vector<string> getVector(string start, char direction, int length, bool include_start = true); // Generates a vector of space strings in a direction.

        // Static methods for finding neighboring spaces.
        static vector<string> neighborSpaces(string space_string); // Returns a vector of neighboring spaces for a given space.
        static vector<string> neighborSpaces(vector<string> space_strings); // Returns a vector of neighboring spaces for multiple spaces.

        // Method to place a stud on a specific space in the grid.
        void setOnSpace(string space, Stud* stud) const;

        // Method to target a specific space and return the result.
        TargetResult target(string space_string) const;

        // Method to display the grid, with an option to show hidden details for Camden (CPU).
        void showGrid(bool show_camden = false) const;
};

#endif // End of include guard.
