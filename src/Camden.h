#ifndef CAMDEN_H
#define CAMDEN_H

#include <string>
    using std::string;

#include <vector>
    using std::vector;

#include "Enums.h"
#include "Grid.h"
#include "Player.h"
#include "Ship.h"

class Camden {
    private:
        Player* self {nullptr};
        Grid* foeGrid {nullptr};
        Ship* curVictimShip {nullptr};
        vector<string> availableSpaces;
        vector<string> attackSpaces;
        vector<char> attackDirections;
        vector<int> numShipsSank;
        string firstAttackSpace;
        string lastAttackSpace;
        char directions[4] {'N','S','E','W'};
        char attackDirection;
        bool isAttackingShip {false};
        bool hasSunkShip {false};
        bool lastAttackSpaceWasEmpty {false};
        
        bool did_just_sink_ship_check1() const;
        bool did_just_sink_ship_check2() const;
        bool did_just_sink_ship() const;
        bool space_is_available(string space) const;
        void set_Camden();
        void switch_direction_to_opposite();
        void update_num_ships_sank();
        void check_for_holes();
        void initiate_attack(string space);
        void remove_attack_direction(char direction);
        void remove_available_space(string space);
        void remove_available_spaces(vector<string> spaces);
        void reset_to_default();
        void do_switch();
        bool is_a_hit(string space) const;
        string pick_direction(int(*rand_func)(), char& direction);
        string pick_attack_space(int(*rand_func)());
        string pick_random_space(int(*rand_func)());
    
    public:
        Camden();
        explicit Camden(Player* the_self);
        ~Camden();
        string makeAMove(int(*rand_func)());
        void badBoy(string space);
        string makeMove(int(*rand_func)(), string bad_space = "");
};

#endif