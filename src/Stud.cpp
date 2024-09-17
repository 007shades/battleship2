#include "Stud.h"

#include "Enums.h"

void Stud::set_ship_type(StudName stud_name){
    int stud_int = static_cast<int>(stud_name);
    if (stud_int < 5)
        this->forShip = Carrier;
    else if (stud_int < 9)
        this->forShip = Battleship;
    else if (stud_int < 12)
        this->forShip = Destroyer;
    else if (stud_int < 15)
        this->forShip = Submarine;
    else
        this->forShip = Cruiser;
}

Stud::Stud() {}

Stud::Stud(StudName stud_name) : studName{stud_name} {
    set_ship_type(stud_name);
}

Stud::Stud(StudName stud_name, SpaceName on_space) : studName{stud_name}, onSpace {on_space} 
{
    set_ship_type(stud_name);
}

Stud::Stud(StudName stud_name, SpaceName on_space, PlayerType of_player) : studName{stud_name}, onSpace {on_space}, ofPlayer {of_player}
{
    set_ship_type(stud_name);
}

Stud::Stud(StudName stud_name, SpaceName on_space, PlayerType of_player, StudStatus the_status) : studName{stud_name}, onSpace {on_space}, ofPlayer {of_player}, status {the_status}
{
    set_ship_type(stud_name);
}