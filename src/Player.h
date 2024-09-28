#ifndef PLAYER_H
#define PLAYER_H

#include "Enums.h"
#include "Ship.h"
#include "Grid.h"

#include <array>
    using std::array;
#include <vector>
    using std::vector;
#include <string>
    using std::string;

class Player {
    private:
        PlayerType type;
        string name;
        Grid* grid {nullptr};
        Player* foe {nullptr};
        Grid* foeGrid {nullptr};
        array<Ship*, 5> ships;
        vector<Ship*> floatingShips;
        vector<Ship*> sunkenShips;
        vector<string> targetedSpaces;
        vector<string> hitSpaces;
        vector<string> missSpaces;
        vector<char> HMHist;

    public:
        Player();
        explicit Player(PlayerType player_type);
        Player(PlayerType player_type, string player_name);
        Player(PlayerType player_type, string player_name, Player* the_foe);
        ~Player();
        PlayerType getPlayerType() const;
        string getName() const;
        Grid* getGrid() const;
        Player* getFoe() const;
        Grid* getFoeGrid() const;
        array<Ship*, 5> getShips() const;
        vector<Ship*> getFloatingShips() const;
        vector<Ship*> getSunkenShips() const;
        vector<string> getTargetedSpaces() const;
        vector<string> getHitSpaces() const;
        vector<string> getMissSpaces() const;
        vector<char> getHMHist() const;
        void setPlayerType(PlayerType player_type);
        void setName(string name);
        void setFoe(Player* the_foe);
        void setFoeGrid(Grid* the_grid);

        void makeFoe(Player* the_foe);

        bool hasShip(Ship* ship) const;
        bool shipIsFloating(Ship* ship) const;
        bool shipIsSunken(Ship* ship) const;

        void stillFloating() const;
        void notSunkYet() const;
        void showFoe() const;
        void showOwn() const;

        Ship* justSunkenShip() const;

        void sinkShip(Ship* ship);

        bool spaceWasTargeted(string space) const;
        
        bool target(string space);

        bool processInput(string input);
        
        bool allShipsAreSunk() const;

        void setCarrier();
        void setBattleship();
        void setDestroyer();
        void setSubmarine();
        void setCruiser();
        void manuallySetShips();
};

#endif