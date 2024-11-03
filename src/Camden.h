#ifndef CAMDEN_H // Include guard to prevent multiple inclusions.
#define CAMDEN_H

#include <string> // Include string for text handling.
    using std::string; // Use string from the standard namespace.

#include <vector> // Include vector for dynamic array handling.
    using std::vector; // Use vector from the standard namespace.

#include "Enums.h" // Include Enums for predefined enumerations.
#include "Grid.h" // Include Grid for grid operations.
#include "Player.h" // Include Player class for player interactions.

// Declaration of the Camden class.
class Camden {
    private:
        Player* self {nullptr}; // Pointer to the player object.
        Grid* foeGrid {nullptr}; // Pointer to the foe's grid.
        vector<string> availableSpaces; // List of available spaces for attacks.
        vector<string> attackSpaces; // List of spaces targeted during an attack.
        vector<char> attackDirections; // List of potential attack directions.
        vector<int> numShipsSank; // Number of ships sunk by the player.
        string firstAttackSpace; // The first space of the current attack.
        string lastAttackSpace; // The last space hit during the current attack.
        char directions[4] {'N','S','E','W'}; // Array of possible attack directions.
        char attackDirection; // Current attack direction.
        bool isAttackingShip {false}; // Indicates if currently attacking a ship.
        bool lastAttackSpaceWasEmpty {false}; // Indicates if the last space was empty.
        
        // Private helper methods.
        bool did_just_sink_ship() const; // Checks if a ship was just sunk.
        bool space_is_available(string space) const; // Checks if a space is available for attack.
        void set_Camden(); // Initializes Camden's attributes.
        void reset_to_default(); // Resets Camden's state to default values.
        void switch_direction_to_opposite(); // Switches the current attack direction to its opposite.
        void update_num_ships_sank(); // Updates the number of ships sunk.
        void check_for_holes(); // Identifies and removes holes in the attackable spaces.
        void initiate_attack(string space); // Initiates an attack on a specific space.
        void remove_attack_direction(char direction); // Removes an attack direction from the list.
        void remove_available_space(string space); // Removes a space from availableSpaces.
        void remove_available_spaces(vector<string> spaces); // Removes multiple spaces from availableSpaces.
        void do_switch(); // Switches direction and resets the last attack space.
        bool is_a_hit(string space) const; // Checks if a space contains a part of a ship (hit).
        string pick_direction(int(*rand_func)(), char& direction); // Picks a new attack direction.
        string pick_attack_space(int(*rand_func)()); // Picks the next attack space.
        string pick_random_space(int(*rand_func)()); // Picks a random space to attack.
    
    public:
        // Constructors and Destructor.
        Camden(); // Default constructor.
        explicit Camden(Player* the_self); // Constructor initializing Camden with a player.
        ~Camden(); // Destructor to clean up resources.

        // Public method for making a move.
        string makeMove(int(*rand_func)()); // Determines and returns the next move based on attack state.
};

#endif // End of include guard.
