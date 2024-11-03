#ifndef CAMDEN_H // Include guard to prevent multiple inclusions.
#define CAMDEN_H

#include <string> // Include string for handling text.
    using std::string; // Use string from standard namespace.

#include <vector> // Include vector for dynamic array operations.
    using std::vector; // Use vector from standard namespace.

#include "Enums.h" // Include for enumerated types used in the class.
#include "Grid.h" // Include for handling grid operations.
#include "Player.h" // Include for player interactions.

// Declaration of the Camden class.
class Camden {
    private:
        Player* self {nullptr}; // Pointer to the player object (owning player).
        Grid* foeGrid {nullptr}; // Pointer to the opponent's grid.
        vector<string> availableSpaces; // Vector of available spaces for attacks.
        vector<string> attackSpaces; // Vector of spaces currently targeted for attack.
        vector<char> attackDirections; // Vector of possible attack directions.
        vector<int> numShipsSank; // Vector to track the number of ships sunk.
        string firstAttackSpace; // The first space chosen for an attack sequence.
        string lastAttackSpace; // The last space targeted in an attack sequence.
        char directions[4] {'N', 'S', 'E', 'W'}; // Array of possible attack directions.
        char attackDirection; // Current direction of attack.
        bool isAttackingShip {false}; // Flag indicating if a ship is currently being targeted.
        bool lastAttackSpaceWasEmpty {false}; // Flag indicating if the last attack space was empty.

        // Private helper methods.
        bool did_just_sink_ship() const; // Checks if the last move resulted in sinking a ship.
        bool space_is_available(string space) const; // Checks if a space is available for attack.
        void set_Camden(); // Initializes Camden's available spaces and attack directions.
        void reset_to_default(); // Resets Camden's state to default values.
        void switch_direction_to_opposite(); // Switches the attack direction to its opposite.
        void update_num_ships_sank(); // Updates the vector tracking the number of ships sunk.
        void check_for_holes(); // Checks for and removes spaces with no valid neighbors.
        void initiate_attack(string space); // Starts an attack sequence from a given space.
        void remove_attack_direction(char direction); // Removes a direction from the possible attack directions.
        void remove_available_space(string space); // Removes a specific space from the available spaces.
        void remove_available_spaces(vector<string> spaces); // Removes multiple spaces from the available spaces.
        void do_switch(); // Switches the attack direction and resets last attack space to first.
        bool is_a_hit(string space) const; // Checks if a space contains a ship part (stud).
        string pick_direction(int(*rand_func)(), char& direction); // Picks a new attack direction.
        string pick_attack_space(int(*rand_func)()); // Picks the next space to attack.
        string pick_random_space(int(*rand_func)()); // Picks a random space to attack.

    public:
        // Constructors and Destructor.
        Camden(); // Default constructor.
        explicit Camden(Player* the_self); // Constructor taking a Player pointer.
        ~Camden(); // Destructor to clean up resources.

        // Public method.
        string makeMove(int(*rand_func)()); // Makes a move by either continuing an attack or picking a random space.
};

#endif // End of include guard.
