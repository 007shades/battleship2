#ifndef SUBMARINE_H
#define SUBMARINE_H

#include "Enums.h"
#include "Stud.h"
#include "Grid.h"

#include <string>
    using std::string;

#include <array>
    using std::array;

#include "Ship.h"

class Submarine : public Ship {
    private:
        array<Stud*, 3> studs;
    public:
        Submarine();
        explicit Submarine(PlayerType of_player);
        explicit Submarine(Grid* on_grid);
        Submarine(Grid* on_grid, string start_space, char direction);
        ~Submarine();
        array<Stud*, 3> getStuds() const;
        Stud* getStud(StudName stud_name) const;
        bool hasStud(Stud* stud) const override;
        void setStuds() override;
        bool placeOnGrid(string start_space, char direction) const override;
};

#endif