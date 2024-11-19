#ifndef GRID_H
#define GRID_H

#include <array>   // Provides the array container class.
    using std::array;

#include <string>  // Provides the string class.
    using std::string;

#include <vector>  // Provides the vector container class.
    using std::vector;

#include "Enums.h"      // Includes game-related enumerations.
#include "GridSpace.h"  // Includes the GridSpace class for individual grid spaces.

// ** Grid Class **
// Represents a 10x10 grid for managing spaces, ship placement, and targeting.
class Grid {
    private:
        array<GridSpace*, 100> grid;       // Array of pointers to GridSpace objects (10x10 grid).
        PlayerType ofPlayer;              // Specifies the player this grid belongs to.
        vector<SpaceName> noGoSpaces;     // List of restricted spaces where ships cannot be placed.

        // Private helper methods for initializing the grid.
        void populate_grid();                     // Populates the grid with nullptr values.
        void populate_grid(PlayerType of_player); // Populates the grid with GridSpace objects for a specific player.

    public:
        // ** Constructors and Destructor **
        Grid();                                   // Default constructor.
        explicit Grid(PlayerType of_player);      // Constructor for a specific player.
        ~Grid();                                  // Destructor to clean up allocated memory.

        // ** Getters **
        array<GridSpace*, 100> getGrid() const;   // Returns the grid array.
        PlayerType getOfPlayer() const;           // Returns the player associated with this grid.
        vector<SpaceName> getNoGoSpaces() const;  // Returns the list of restricted spaces.

        // ** Setters and Modifiers **
        void setGrid(array<GridSpace*, 100> the_grid); // Sets the grid array.
        void setOfPlayer(PlayerType of_player);        // Sets the player associated with this grid.
        void addNoGoSpace(SpaceName space);            // Adds a single restricted space.
        void addNoGoSpaces(vector<string> space_strings); // Adds multiple restricted spaces from strings.

        // ** Grid Space Accessors **
        GridSpace* getSpace(SpaceName space_name) const; // Gets a specific space by SpaceName.
        GridSpace* getSpace(string space_string) const;  // Gets a specific space by its string representation.
        GridSpace* getSpace(Column column, Row row) const; // Gets a space by column and row.
        GridSpace* getSpace(int column_number, int row_number) const; // Gets a space by numeric column and row.

        // ** "No-Go" Space Checks **
        bool isNoGoSpace(string space_string) const; // Checks if a space is restricted by its string representation.
        bool isNoGoSpace(SpaceName space_name) const; // Checks if a space is restricted by SpaceName.
        bool hasNoGoSpace(vector<string> space_strings) const; // Checks if any given spaces are restricted.

        // ** Directional Movement **
        static string N(string start); // Moves north from a starting space.
        static string S(string start); // Moves south from a starting space.
        static string E(string start); // Moves east from a starting space.
        static string W(string start); // Moves west from a starting space.
        static string goDirection(string start, char direction); // Moves in a specified direction.

        // ** Neighbor and Vector Operations **
        static vector<string> getVector(string start, char direction, int length, bool include_start = true); 
        // Gets a vector of spaces in a direction.

        static vector<string> neighborSpaces(string space_string); // Gets neighbors of a single space.
        static vector<string> neighborSpaces(vector<string> space_strings); // Gets neighbors of multiple spaces.

        // ** Grid Operations **
        void setOnSpace(string space, Stud* stud) const; // Places a stud on a specific space.
        TargetResult target(string space_string) const;  // Targets a space and returns the result.

        // ** Display **
        void showGrid(bool show_camden = false) const; // Displays the grid, optionally revealing hidden spaces.
};

#endif
