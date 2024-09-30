#include "Game.h"
#include <iostream>
    using std::cin;
    using std::cout;
    using std::endl;
#include <string>
    using std::string;
#include <cstdlib>
#include <ctime>

void set_name(string& name);

int main(){
    srand(static_cast<unsigned int>(time(0)));
    string name;
    set_name(name);
    Game* game = new Game(name, &rand);
    delete game;
    game = nullptr;
    return 0;
}

void set_name(string& name) {
    cout << "Enter your name: ";
    cin >> name;
    while(name == "Camden") {
        cout << "Camden is the name of your opponent. Please enter a different name." << endl;
        cout << "Enter your name: ";
        cin >> name;
    }
    cout << "" << endl;
}