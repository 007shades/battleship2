#ifndef CAMDEN_H
#define CAMDEN_H

#include <string>
    using std::string;

#include <vector>
    using std::vector;

#include "Enums.h"
#include "Grid.h"
#include "Player.h"

class Camden {
    private:
        Player* self {nullptr};
        Grid* foeGrid {nullptr};
        vector<string> availableSpaces;
        vector<string> attackSpaces;
        vector<char> attackDirections;
        vector<int> numShipsSank;
        string firstAttackSpace;
        string lastAttackSpace;
        string lastSpaceBeforeChange;
        char directions[4] {'N','S','E','W'};
        char attackDirection;
        bool isAttackingShip {false};
        bool lastAttackSpaceWasEmpty {false};
        bool lastAttackSpaceWasBad {false};
        bool changeJustHappened {false};
        
        bool did_just_sink_ship() const;
        void set_Camden();
        void reset_to_default();
        void switch_direction_to_opposite();
        void update_num_ships_sank();
        void remove_available_spaces();
        void initiate_attack();
        void check_for_holes();
        void remove_attack_direction(char direction);
        void remove_available_space(string space);
        void remove_available_spaces(vector<string> spaces);
        void pick_random_space(int(*rand_func)());
        void pick_attack_space(int(*rand_func)());
    
    public:
        Camden();
        explicit Camden(Player* the_self);
        ~Camden();
        string makeMove(int(*rand_func)());
};

#endif