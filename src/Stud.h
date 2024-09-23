/*A Stud is a section of a Ship. Think of Studs as the holes in the plastic ships 
in the real life game of battleship. Once all the Studs on a Ship have been hit, 
the Ship will sink.*/

#ifndef STUD_H
#define STUD_H

#include "Enums.h"

#include "GridSpace.h"

class GridSpace;

class Stud {
    private:
        StudName studName;
        SpaceName onSpace;
        ShipType forShip;
        PlayerType ofPlayer;
        StudStatus status {INTACT};
        GridSpace* gridspace {nullptr};
        char label;
        void set_ship_type(StudName stud_name);
    public:
        Stud();
        explicit Stud(StudName stud_name);
        Stud(StudName stud_name, GridSpace* grid_space);
        Stud(StudName stud_name, PlayerType of_player);
        Stud(StudName stud_name, GridSpace* grid_space, StudStatus the_status);
        Stud(StudName stud_name, PlayerType of_player, StudStatus the_status);
        ~Stud();
        StudName getStudName() const;
        SpaceName getOnSpace() const;
        ShipType getForShip() const;
        PlayerType getOfPlayer() const;
        StudStatus getStatus() const;
        char getLabel() const;
        void setStudName(StudName stud_name);
        void setOnSpace(SpaceName on_space);
        void setOfPlayer(PlayerType for_player);
        void setStatus(StudStatus stud_status);
        void setLabel(char stud_label);
        bool wasHit() const;
        void hit();
};

#endif