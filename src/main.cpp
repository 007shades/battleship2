#include "Game.h" // Include Game header file.
#include <iostream> // Include for input-output operations.
    using std::cin; // Use cin for console input.
    using std::cout; // Use cout for console output.
    using std::endl; // Use endl for line breaks.
#include <string> // Include for handling strings.
    using std::string; // Use string from the standard namespace.
#include <cstdlib> // Include for rand and srand functions.
#include <ctime> // Include for time function to seed random number generator.

// Function prototype to set the player's name.
void set_name(string& name);

// Main function: Entry point of the program.
int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator with the current time.
    string name; // Variable to store the player's name.
    set_name(name); // Call function to set the player's name.
    
    // Create a new game instance and pass the player's name and the rand function pointer.
    Game* game = new Game(name, &rand);
    
    // Clean up by deleting the game instance.
    delete game;
    game = nullptr; // Set pointer to nullptr to avoid dangling pointers.
    
    return 0; // Exit the program.
}

// Function to prompt the user to enter their name.
void set_name(string& name) {
    cout << "Enter your name: "; // Prompt for name.
    cin >> name; // Read the player's name from input.
    
    // Check if the name is "Camden" and prompt for a different name if it is.
    while(name == "Camden") {
        cout << "Camden is the name of your opponent. Please enter a different name." << endl;
        cout << "Enter your name: "; // Prompt for a new name.
        cin >> name; // Read the new name from input.
    }
    cout << "" << endl; // Print an empty line for formatting.
}
