#ifndef CRUISER_H
#define CRUISER_H

#include "Enums.h"
#include "Stud.h"
#include "Grid.h"

#include <string>
    using std::string;

#include <array>
    using std::array;

#include "Ship.h"

class Cruiser : public Ship {
    private:
        array<Stud*, 2> studs;
    public:
        Cruiser();
        explicit Cruiser(PlayerType of_player);
        explicit Cruiser(Grid* on_grid);
        Cruiser(Grid* on_grid, string start_space, char direction);
        ~Cruiser();
        array<Stud*, 2> getStuds() const;
        Stud* getStud(StudName stud_name) const;
        bool hasStud(Stud* stud) const override;
        void setStuds() override;
        bool placeOnGrid(string start_space, char direction) const override;

};

#endif