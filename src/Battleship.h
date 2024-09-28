#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include "Enums.h"
#include "Stud.h"
#include "Grid.h"

#include <string>
    using std::string;

#include <array>
    using std::array;

#include "Ship.h"

class Battleship : public Ship {
    private:
        array<Stud*, 4> studs;
    public:
        Battleship();
        explicit Battleship(PlayerType of_player);
        explicit Battleship(Grid* on_grid);
        Battleship(Grid* on_grid, string start_space, char direction);
        ~Battleship();
        array<Stud*, 4> getStuds() const;
        Stud* getStud(StudName stud_name) const;
        bool hasStud(Stud* stud) const override;
        void setStuds() override;
        bool placeOnGrid(string start_space, char direction, bool print_out = true) const override;

};

#endif