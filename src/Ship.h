#ifndef SHIP_H
#define SHIP_H

#include "Enums.h"
#include "Grid.h"
#include "Stud.h"

#include <vector>
    using std::vector;

#include <string>
    using std::string;

class Stud;

class Ship {
    protected:
        PlayerType ofPlayer;
        Grid* onGrid {nullptr};
        vector<Stud*> intactStuds;
        vector<Stud*> destroyedStuds;
        ShipType shipType;
        ShipStatus status {AFLOAT};
        bool isOnGrid {false};
        bool isReady {false};
    public:
        Ship();
        explicit Ship(ShipType ship_type);
        Ship(ShipType ship_type, PlayerType of_player);
        Ship(ShipType ship_type, Grid* on_grid);
        ~Ship();
        
        PlayerType getOfPlayer() const;
        Grid* getOnGrid() const;
        vector<Stud*> getIntactSutds() const;
        vector<Stud*> getDestroyedStuds() const;
        ShipType getShipType() const;
        ShipStatus getShipStatus() const;
        bool getIsOnGrid() const;
        void setOfPlayer(PlayerType of_player);
        void setGrid(Grid* on_grid);
        void setShipType(ShipType ship_type);
        void setShipStatus(ShipStatus ship_status);
        void setIsOnGrid(bool is_on_grid);
        bool studIsIntact(Stud* stud) const;
        virtual void setStuds() = 0;
        virtual bool hasStud(Stud* stud) const = 0;
        virtual bool placeOnGrid(string start_space, char direction) const = 0;
        void destroyStud(Stud* stud);

};

#endif