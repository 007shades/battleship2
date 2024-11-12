#include "Game.h"

#include "Camden.h"
#include "Enums.h"
#include "Player.h"

#include <string>
    using std::string;

#include <iostream>
    using std::cout;
    using std::cin;
    using std::endl;

#include <unistd.h> //Sleep function

#include <stdexcept>
    using std::logic_error;

Game::Game() {}

Game::Game(string human_name) {
    this->cpu = new Player(CPU);
    this->human = new Player(MAN, human_name);
}

Game::Game(string human_name, int(*rand_func)()) : Game(human_name) {
    this->doSetUp(rand_func);
    this->doCoinToss(rand_func);
    this->doFinalSetup();
    this->playGame(rand_func);
}

Game::~Game() {
    delete this->human;
    this->human = nullptr;
    delete this->cpu;
    this->cpu = nullptr;
    delete this->camden;
    this->camden = nullptr;
}

Player* Game::getHuman() const {
    return this->human;
}

Player* Game::getCpu() const {
    return this->cpu;
}

Camden* Game::getCamden() const {
    return this->camden;
}

PlayerType Game::getTurn() const {
    return this->turn;
}

void Game::setHuman(Player* the_human) {
    this->human = the_human;
}

void Game::setCpu(Player* the_cpu) {
    this->cpu = the_cpu;
}

void Game::setCamden(Camden* new_camden) {
    this->camden = new_camden;
}

void Game::setTurn(PlayerType the_turn) {
    this->turn = the_turn;
}

bool Game::someoneHasWon() const {
    return this->human->allShipsAreSunk() || this->cpu->allShipsAreSunk();
}

PlayerType Game::winner() const {
    if(this->someoneHasWon())
        if(this->human->allShipsAreSunk())
            return CPU;
        else
            return MAN;
    throw logic_error("Nobody has won yet.");
}

void Game::switchTurn() {
    switch(this->turn) {
        case MAN:
            this->turn = CPU;
            break;
        case CPU:
        default:
            this->turn = MAN;
    }
}

void Game::doCpuTurn(int(*rand_func)()) const {
    string bad_space = "NA";
    bool good_space_chosen = false;
    string camden_space;
    do {
        camden_space = this->camden->makeMove(rand_func, bad_space);
        good_space_chosen = this->cpu->target(camden_space, false);
        if(!good_space_chosen)bad_space = camden_space;
    } while (!good_space_chosen);
}

void Game::doHumanTurn() const {
    this->human->doTurn();
}

void Game::doTurn(int(*rand_func)()) {
    if(this->turn == CPU)
        this->doCpuTurn(rand_func);
    else if(this->turn == MAN)
        this->doHumanTurn();
    else
        throw logic_error("It is nobody\'s turn.");
    this->switchTurn();
}

void Game::doSetUp(int(*rand_func)()) {
    this->human->askToSetShips(rand_func);
    cout << "\nCamden is setting his ships..." << endl;
    this->cpu->autoSetShips(rand_func);
    sleep(1);
    cout << "   Done." << endl;
}

void Game::doCoinToss(int(*rand_func)()) {
    char user_coin_choice;
    cout << "" << endl;
    cout << "Coin toss! Winner goes first. Heads or Tails?" << endl;
    cout << "(H / h or T / t) > ";
    cin >> user_coin_choice;
    int coin_toss = rand_func() % 2;
    if (!coin_toss){
        if(user_coin_choice == 'H' || user_coin_choice == 'h') {
            cout << "It\'s Heads, you won the toss and will go first." << endl;
            this->turn = MAN;
        } else {
            cout << "It\'s Heads, you lost the toss and will go second." << endl;
            this->turn = CPU;
        }
    } else {
        if(user_coin_choice == 'T' || user_coin_choice == 't') {
            cout << "It\'s Tails, you won the toss and will go first." << endl;
            this->turn = MAN;
        } else {
            cout << "It\'s Tails, you lost the toss and will go second." << endl;
        }
    }
    sleep(1);
    cout << "" << endl;
    cout << "Loading Game..." << endl;
    sleep(1);
    cout << "" << endl;
}

void Game::doFinalSetup() {
    this->human->makeFoe(this->cpu);
    this->cpu->makeFoe(this->human);
    this->camden = new Camden(this->cpu);
}

void Game::playGame(int(*rand_func)()){
    do {
        cout << "" << endl;
        this->doTurn(rand_func);
        sleep(1);
        cout << "" << endl;
    } while (!(this->someoneHasWon()));
    if(this->someoneHasWon()){
        cout << "" << endl;
        if(this->winner() == CPU) {
            cout << "Camden wins!" << endl;
            sleep(1);
            cout << "" << endl;
            cout << "Here is Camden\'s grid: " << endl;
            cout << "" << endl;
            this->cpu->getGrid()->showGrid(true);
        }
    } else cout << "You win!" << endl;
}