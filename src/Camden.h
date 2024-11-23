#ifndef CAMDEN_H
#define CAMDEN_H

#include <string>
    using std::string; // To manage player and space names.
#include <vector>
    using std::vector; // For dynamic lists of spaces, directions, and other data.

#include "Enums.h"     // Definitions for game-related enumerations.
#include "Grid.h"      // To access and manipulate the game grid.
#include "Player.h"    // For interactions with the player class.
#include "Ship.h"      // For managing ship-related operations.

class Camden {
    private:
        Player* self {nullptr}; // Reference to Camden's player instance.
        Grid* foeGrid {nullptr}; // Reference to the opponent's grid for attacks.
        Ship* curVictimShip {nullptr}; // Pointer to the ship Camden is currently attacking.

        // **Dynamic Game State Tracking**
        vector<string> availableSpaces; // List of spaces Camden can target.
        vector<string> attackSpaces;    // List of spaces currently involved in an attack sequence.
        vector<char> attackDirections; // Directions Camden is considering for attacks.
        vector<int> numShipsSank;      // History of the number of ships sunk by Camden.

        // **Attack State Management**
        string firstAttackSpace; // First space hit in the current attack sequence.
        string lastAttackSpace;  // Most recent space hit in the current attack sequence.
        char directions[4] {'N','S','E','W'}; // Fixed array of possible attack directions.
        char attackDirection; // Current direction of attack.

        // **State Flags**
        bool isAttackingShip {false}; // True if Camden is actively targeting a specific ship.
        bool hasSunkShip {false};     // True if a ship was sunk during this attack sequence.
        bool lastAttackSpaceWasEmpty {false}; // True if the last space targeted was empty.

        // **Private Helper Methods**
        bool did_just_sink_ship_check1() const; // Checks if the number of sunk ships changed.
        bool did_just_sink_ship_check2() const; // Checks if the current victim ship was just sunk.
        bool did_just_sink_ship() const;        // Combines the two sinking checks.

        bool space_is_available(string space) const; // Validates if a space is targetable.
        void set_Camden();                           // Initializes Camden's default state.
        void switch_direction_to_opposite();         // Reverses the attack direction.
        void update_num_ships_sank();                // Updates the count of sunk ships.
        void check_for_holes();                      // Removes isolated spaces from target list.
        void initiate_attack(string space);          // Starts targeting a specific ship.
        void remove_attack_direction(char direction); // Removes a direction from possible attacks.
        void remove_available_space(string space);    // Removes a specific space from available targets.
        void remove_available_spaces(vector<string> spaces); // Removes multiple spaces from available targets.
        void reset_to_default();                     // Resets Camden's attack state.
        void do_switch();                            // Switches attack direction during an attack sequence.
        bool is_a_hit(string space) const;           // Checks if a space contains a ship's stud.
        string pick_direction(int(*rand_func)(), char& direction); // Picks a valid direction for attack.
        string pick_attack_space(int(*rand_func)()); // Determines the next space to attack based on current strategy.
        string pick_random_space(int(*rand_func)()); // Selects a random space from available targets.

    public:
        // **Constructors and Destructor**
        Camden();                   // Default constructor.
        explicit Camden(Player* the_self); // Constructor initializing Camden with a reference to its player.
        ~Camden();                  // Destructor to clean up pointers.

        // **Public Methods**
        string makeAMove(int(*rand_func)()); // Main method to determine Camden's move during its turn.
        void badBoy(string space);          // Marks a space as invalid and removes it from targets.
        string makeMove(int(*rand_func)(), string bad_space = ""); // Handles Camden's move logic, incorporating invalid spaces.
};

#endif
