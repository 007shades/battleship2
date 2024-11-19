#ifndef CAMDEN_H
#define CAMDEN_H

#include <string>   // Provides the string class.
    using std::string;

#include <vector>   // Provides the vector container.
    using std::vector;

#include "Enums.h"  // Includes enumerations used in the class.
#include "Grid.h"   // Includes the Grid class for managing the game board.
#include "Player.h" // Includes the Player class.
#include "Ship.h"   // Includes the Ship class.

class Camden {
    private:
        Player* self {nullptr};               // Pointer to the current player.
        Grid* foeGrid {nullptr};             // Pointer to the opponent's grid.
        Ship* curVictimShip {nullptr};       // Pointer to the ship currently being attacked.
        vector<string> availableSpaces;      // List of spaces that are still available for attack.
        vector<string> attackSpaces;         // List of spaces involved in the current attack sequence.
        vector<char> attackDirections;       // List of possible attack directions.
        vector<int> numShipsSank;            // Tracks the number of ships sunk over time.
        string firstAttackSpace;             // The starting space of the current attack sequence.
        string lastAttackSpace;              // The most recent space attacked in the current sequence.
        char directions[4] {'N','S','E','W'}; // Array of possible attack directions (North, South, East, West).
        char attackDirection;                // Current direction of attack.
        bool isAttackingShip {false};        // Whether an attack on a specific ship is ongoing.
        bool hasSunkShip {false};            // Whether a ship has been sunk during the current attack.
        bool lastAttackSpaceWasEmpty {false}; // Whether the last attacked space was empty.

        // Private utility methods
        bool did_just_sink_ship_check1() const;  // Check if a ship was sunk using the numShipsSank vector.
        bool did_just_sink_ship_check2() const;  // Check if the current victim ship was just sunk.
        bool did_just_sink_ship() const;         // Determines if a ship was just sunk using the above checks.
        bool space_is_available(string space) const; // Checks if a specific space is available for attack.
        void set_Camden();                       // Initializes Camden's state (directions, spaces, etc.).
        void switch_direction_to_opposite();     // Switches the current attack direction to its opposite.
        void update_num_ships_sank();            // Updates the list of sunk ships.
        void check_for_holes();                  // Removes spaces with no valid neighbors from availableSpaces.
        void initiate_attack(string space);      // Begins an attack sequence on a specific space.
        void remove_attack_direction(char direction); // Removes a direction from attackDirections.
        void remove_available_space(string space);    // Removes a space from availableSpaces.
        void remove_available_spaces(vector<string> spaces); // Removes multiple spaces from availableSpaces.
        void reset_to_default();                 // Resets Camden's state to the default values.
        void do_switch();                        // Switches to the opposite attack direction.
        bool is_a_hit(string space) const;       // Checks if a space is a hit (contains a stud).
        string pick_direction(int(*rand_func)(), char& direction); // Picks a direction and a corresponding space.
        string pick_attack_space(int(*rand_func)());  // Selects a space to attack using the current strategy.
        string pick_random_space(int(*rand_func)());  // Selects a random space to attack.

    public:
        Camden();                                // Default constructor.
        explicit Camden(Player* the_self);      // Constructor with a Player object.
        ~Camden();                               // Destructor to clean up resources.
        string makeAMove(int(*rand_func)());     // Determines and executes the next move.
        void badBoy(string space);              // Removes a space from availableSpaces as a "bad" space.
        string makeMove(int(*rand_func)(), string bad_space = ""); // Combines strategy and manual moves.
};

#endif
