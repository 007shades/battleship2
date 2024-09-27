#ifndef CARRIER_H
#define CARRIER_H

#include "Enums.h"
#include "Stud.h"
#include "Grid.h"

#include <string>
    using std::string;

#include <array>
    using std::array;

#include "Ship.h"

class Carrier : public Ship {
    private:
        array<Stud*, 5> studs;
    public:
        Carrier();
        explicit Carrier(PlayerType of_player);
        explicit Carrier(Grid* on_grid);
        Carrier(Grid* on_grid, string start_space, char direction);
        ~Carrier();
        array<Stud*, 5> getStuds() const;
        Stud* getStud(StudName stud_name) const;
        bool hasStud(Stud* stud) const override;
        void setStuds() override;
        bool placeOnGrid(string start_space, char direction) const override;

};

#endif