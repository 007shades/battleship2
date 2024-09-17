/*A Stud is a section of a Ship. Think of Studs as the holes in the plastic ships 
in the real life game of battleship. Once all the Studs on a Ship have been hit, 
the Ship will sink.*/

#ifndef STUD_H
#define STUD_H

#include "Enums.h"

class Stud {
    private:
        StudName studName;
        SpaceName onSpace;
        ShipType forShip;
        PlayerType ofPlayer;
        StudStatus status {INTACT};
        void set_ship_type(StudName stud_name);
    public:
        Stud();
        explicit Stud(StudName stud_name);
        Stud(StudName stud_name, SpaceName on_space);
        Stud(StudName stud_name, SpaceName on_space, PlayerType of_player);
        Stud(StudName stud_name, SpaceName on_space, PlayerType of_player, StudStatus the_status);
        ~Stud() = default;
        StudName getStudName() const;
        SpaceName getSpaceName() const;
        ShipType getForShip() const;
        PlayerType getOfPlayer() const;
        StudStatus getStudStatus() const;
        void setStudName(StudName stud_name);
        void setForSpace(SpaceName on_space);
        void setOfPlayer(PlayerType for_player);
        void setStudStatus(StudStatus stud_status);
        bool wasHit() const;
        void hit();
};

#endif