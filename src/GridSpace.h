#ifndef GRIDSPACE_H // Include guard to prevent multiple inclusions.
#define GRIDSPACE_H

#include <string> // Include for using the string class.
    using std::string; // Use string from the standard namespace.

#include "Enums.h" // Include for enumerated types used in the class.
#include "Stud.h" // Include for the Stud class representing parts of ships.

class Stud; // Forward declaration of Stud class to avoid circular dependency.

// Declaration of the GridSpace class representing a space on the grid.
class GridSpace {
    private:
        SpaceName spaceName; // The name of the space (e.g., A1, B2).
        Column column; // The column the space is in.
        Row row; // The row the space is in.
        PlayerType ofPlayer; // The player who owns this space (e.g., CPU or human).
        SpaceStatus status {UNTARGETED}; // The status of the space (UNTARGETED or TARGETED).
        Stud* stud {nullptr}; // Pointer to a Stud object if the space contains a part of a ship.
        string spaceString; // String representation of the space (e.g., "A1").
        char label {'+'}; // Label to display on the grid (e.g., '+' for untargeted, 'H' for hit).
        char primeLabel {'+'}; // Alternative label for hidden states (e.g., for the CPU's view).
        char letter; // The column letter of the space (e.g., 'A').
        char number; // The row number of the space as a character (e.g., '1').
        
        // Private method to set additional data for the space based on its name.
        void set_space_data(SpaceName space_name);

    public:
        // Constructors and Destructor.
        GridSpace(); // Default constructor.
        explicit GridSpace(SpaceName space_name); // Constructor initializing space with a SpaceName.
        GridSpace(SpaceName space_name, PlayerType of_player); // Constructor with SpaceName and player type.
        GridSpace(SpaceName space_name, PlayerType of_player, SpaceStatus space_status); // Constructor with SpaceName, player type, and status.
        GridSpace(SpaceName space_name, PlayerType of_player, SpaceStatus space_status, Stud* the_stud); // Constructor with all parameters.
        ~GridSpace(); // Destructor to clean up resources.

        // Getter methods.
        SpaceName getSpaceName() const; // Returns the SpaceName of the GridSpace.
        Column getColumn() const; // Returns the Column of the GridSpace.
        Row getRow() const; // Returns the Row of the GridSpace.
        PlayerType getOfPlayer() const; // Returns the PlayerType associated with the GridSpace.
        SpaceStatus getStatus() const; // Returns the SpaceStatus of the GridSpace.
        Stud* getStud() const; // Returns the Stud on the GridSpace.
        string getSpaceString() const; // Returns the string representation of the space.
        char getLetter() const; // Returns the column letter of the GridSpace.
        char getNumber() const; // Returns the row number as a character.
        char getLabel() const; // Returns the label of the GridSpace.
        char getPrimeLabel() const; // Returns the prime label of the GridSpace.

        // Setter methods.
        void setSpaceName(SpaceName space_name); // Sets the SpaceName and updates space data.
        void setOfPlayer(PlayerType of_player); // Sets the PlayerType for the GridSpace.
        void setStatus(SpaceStatus space_status); // Sets the SpaceStatus.
        void setStud(Stud* the_stud); // Sets the Stud on the GridSpace.
        void setLabel(char label); // Sets the label of the GridSpace.

        // Method to add a Stud to the space and update labels.
        void addStud(Stud* the_stud);

        // Methods to check space properties.
        bool hasStud() const; // Checks if the space contains a Stud.
        bool wasTargeted() const; // Checks if the space was targeted.

        // Method to modify the display label based on the space's status and contents.
        void modifyLabel();

        // Method to target the space and return the result (HIT or MISS).
        TargetResult target();
};

#endif // End of include guard.
