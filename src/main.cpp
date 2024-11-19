#include "Game.h" // Includes the Game class, which encapsulates the game's functionality.

#include <iostream>
    using std::cin;  // For user input.
    using std::cout; // For displaying output.
    using std::endl;

#include <string>
    using std::string; // To handle player names.

#include <cstdlib> // For srand and rand.
#include <ctime>   // For seeding the random number generator with the current time.

// ** Function Prototype **
void set_name(string& name); // Function to get the player's name while avoiding conflicts with the opponent's name.

// ** Main Function **
int main() {
    // Seed the random number generator.
    srand(static_cast<unsigned int>(time(0)));

    // ** Get the Player's Name **
    string name;
    set_name(name);

    // ** Create and Start the Game **
    Game* game = new Game(name, &rand); // Dynamically allocate a Game object, passing the player's name and RNG function.
    
    // ** Cleanup **
    delete game;  // Deallocate the Game object after the game ends.
    game = nullptr; // Avoid dangling pointers.

    // ** Exit Program **
    return 0;
}

// ** Helper Function to Set Player's Name **
void set_name(string& name) {
    cout << "Enter your name: "; // Prompt the user for their name.
    cin >> name;

    // Prevent the player from using the name "Camden," which is reserved for the CPU opponent.
    while (name == "Camden") {
        cout << "Camden is the name of your opponent. Please enter a different name." << endl;
        cout << "Enter your name: ";
        cin >> name;
    }
    cout << "" << endl; // Add a blank line for spacing.
}
