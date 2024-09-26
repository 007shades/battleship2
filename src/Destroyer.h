#ifndef DESTROYER_H
#define DESTROYER_H

#include "Enums.h"
#include "Stud.h"
#include "Grid.h"

#include <string>
    using std::string;

#include <array>
    using std::array;

#include "Ship.h"

class Destroyer : public Ship {
    private:
        array<Stud*, 3> studs;
    public:
        Destroyer();
        explicit Destroyer(PlayerType of_player);
        explicit Destroyer(Grid* on_grid);
        ~Destroyer();
        array<Stud*, 3> getStuds() const;
        Stud* getStud(StudName stud_name) const;
        bool hasStud(Stud* stud) const override;
        void setStuds() override;
        bool placeOnGrid(string start_space, char direction) const override;

};

#endif