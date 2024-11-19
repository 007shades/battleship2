#ifndef GRIDSPACE_H
#define GRIDSPACE_H

#include <string>   // Provides the string class.
    using std::string;

#include "Enums.h"  // Includes enumerations for game elements like SpaceName, PlayerType, etc.
#include "Stud.h"   // Includes the Stud class for ship components.

// Forward declaration of the Stud class to avoid circular dependencies.
class Stud;

// ** GridSpace Class **
// Represents a single space on the game grid, managing its state, labels, and associated Stud (if any).
class GridSpace {
    private:
        SpaceName spaceName;         // The name of the space (e.g., A1, B2).
        Column column;               // The column of the space (e.g., ALPHA, BRAVO).
        Row row;                     // The row of the space (e.g., ONE, TWO).
        PlayerType ofPlayer;         // The player who owns this grid space.
        SpaceStatus status {UNTARGETED}; // The targeting status of the space (UNTARGETED or TARGETED).
        Stud* stud {nullptr};        // Pointer to a Stud (ship component) on this space, if any.
        string spaceString;          // String representation of the space (e.g., "A1").
        char label {'+'};            // The label displayed for the space (e.g., '+', 'H', or 'M').
        char primeLabel {'+'};       // The hidden label for the space (e.g., reveals ship position).
        char letter;                 // The column letter (e.g., 'A').
        char number;                 // The row number (e.g., '1').
        
        // Private helper method to set up space data from SpaceName.
        void set_space_data(SpaceName space_name);

    public:
        // ** Constructors and Destructor **
        GridSpace();                                  // Default constructor.
        explicit GridSpace(SpaceName space_name);     // Constructor with a SpaceName.
        GridSpace(SpaceName space_name, PlayerType of_player); // Constructor with SpaceName and PlayerType.
        GridSpace(SpaceName space_name, PlayerType of_player, SpaceStatus space_status); 
        // Constructor with SpaceName, PlayerType, and SpaceStatus.
        GridSpace(SpaceName space_name, PlayerType of_player, SpaceStatus space_status, Stud* the_stud); 
        // Constructor with SpaceName, PlayerType, SpaceStatus, and a Stud.
        ~GridSpace();                                 // Destructor to clean up resources.

        // ** Getters **
        SpaceName getSpaceName() const;               // Returns the SpaceName.
        Column getColumn() const;                    // Returns the column of the space.
        Row getRow() const;                          // Returns the row of the space.
        PlayerType getOfPlayer() const;              // Returns the PlayerType associated with the space.
        SpaceStatus getStatus() const;               // Returns the status of the space.
        Stud* getStud() const;                       // Returns the pointer to the Stud on this space.
        string getSpaceString() const;               // Returns the string representation of the space.
        char getLetter() const;                      // Returns the column letter of the space.
        char getNumber() const;                      // Returns the row number of the space.
        char getLabel() const;                       // Returns the visible label of the space.
        char getPrimeLabel() const;                  // Returns the hidden label of the space.

        // ** Setters **
        void setSpaceName(SpaceName space_name);      // Sets the SpaceName and updates associated data.
        void setOfPlayer(PlayerType of_player);      // Sets the PlayerType of the space.
        void setStatus(SpaceStatus space_status);    // Sets the status of the space.
        void setStud(Stud* the_stud);                // Sets the Stud on the space.
        void setLabel(char label);                   // Sets the visible label of the space.

        // ** Stud Management **
        void addStud(Stud* the_stud);                // Adds a Stud to the space. Throws if already occupied.

        // ** Status Checks **
        bool hasStud() const;                        // Checks if a Stud is present on the space.
        bool wasTargeted() const;                    // Checks if the space has been targeted.

        // ** Label Modification **
        void modifyLabel();                          // Updates the label based on space status and ownership.

        // ** Targeting **
        TargetResult target();                       // Targets the space and returns HIT or MISS.
};

#endif
