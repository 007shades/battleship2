#ifndef GAME_H
#define GAME_H

#include "Enums.h"
#include "Player.h"
#include "Camden.h"

#include <string>
    using std::string;

class Game {
    private:
        Player* human {nullptr};
        Player* cpu {nullptr};
        Camden* camden {nullptr};
        PlayerType turn;
    public:
        Game();
        explicit Game(string human_name);
        Game(string human_name, int(*rand_func)());
        ~Game();
        Player* getHuman() const;
        Player* getCpu() const;
        Camden* getCamden() const;
        PlayerType getTurn() const;
        void setHuman(Player* the_human);
        void setCpu(Player* the_cpu);
        void setCamden(Camden* new_camden);
        void setTurn(PlayerType turn);

        bool someoneHasWon() const;
        PlayerType winner() const;
        
        void switchTurn();
        void doCpuTurn(int(*rand_func)()) const;
        void doHumanTurn() const;
        void doTurn(int(*rand_func)());

        void doSetUp(int(*rand_func)());
        void doCoinToss(int(*rand_func)());
        void playGame(int(*rand_func)());

};

#endif