#include "Grid.h" // Include Grid header file.

#include <array> // Include for using array class.
    using std::array; // Use array from the standard namespace.

#include <string> // Include for using string class.
    using std::string; // Use string from the standard namespace.
    using std::to_string; // Use to_string for integer to string conversion.

#include <vector> // Include for using vector class.
    using std::vector; // Use vector from the standard namespace.

#include <stdexcept> // Include for handling exceptions like out_of_range and invalid_argument.
    using std::out_of_range; // Use out_of_range from the standard namespace.
    using std::invalid_argument; // Use invalid_argument from the standard namespace.

#include <iostream> // Include for input-output operations.
    using std::cout; // Use cout for console output.
    using std::endl; // Use endl for line breaks.

#include "Enums.h" // Include for enumerated types used in the class.

#include "GridSpace.h" // Include for GridSpace class to represent spaces on the grid.

// Method: Populates the grid with nullptr to initialize each space.
void Grid::populate_grid() {
    for(size_t i = 0; i < 100; ++i)
        this->grid[i] = nullptr;
}

// Method: Populates the grid with new GridSpace objects associated with a player.
void Grid::populate_grid(PlayerType of_player) {
    for(size_t i = 0; i < 100; ++i)
        this->grid[i] = new GridSpace(Spaces::spaceNames[i], of_player);
}

// Constructor: Initializes the grid with empty spaces.
Grid::Grid() {
    this->populate_grid(); // Populate grid with nullptr.
}

// Constructor: Initializes the grid and associates it with a player.
Grid::Grid(PlayerType of_player) : ofPlayer{of_player} {
    this->populate_grid(of_player); // Populate grid with GridSpace objects for the player.
}

// Destructor: Cleans up dynamically allocated GridSpace objects.
Grid::~Grid() {
    for(size_t i = 0; i < 100; i++) {
        delete this->grid[i]; // Delete each GridSpace object to free memory.
        this->grid[i] = nullptr; // Set pointer to nullptr to avoid dangling pointers.
    }
}

// Getter: Returns the grid as an array of GridSpace pointers.
array<GridSpace*, 100> Grid::getGrid() const {
    return this->grid;
}

// Getter: Returns the player type associated with the grid.
PlayerType Grid::getOfPlayer() const {
    return this->ofPlayer;
}

// Getter: Returns a vector of "no-go" spaces.
vector<SpaceName> Grid::getNoGoSpaces() const {
    return this->noGoSpaces;
}

// Setter: Sets the grid with a given array of GridSpace pointers.
void Grid::setGrid(array<GridSpace*, 100> the_grid) {
    this->grid = the_grid;
}

// Setter: Sets the player type associated with the grid.
void Grid::setOfPlayer(PlayerType of_player) {
    this->ofPlayer = of_player;
}

// Method: Adds a space to the "no-go" list if it is not already present.
void Grid::addNoGoSpace(SpaceName space) {
    if(!this->isNoGoSpace(space))
        this->noGoSpaces.push_back(space);
}

// Method: Adds multiple spaces to the "no-go" list using a vector of space strings.
void Grid::addNoGoSpaces(vector<string> space_strings) {
    for(string space_string : space_strings)
        this->addNoGoSpace(Spaces::nameFromString(space_string));
}

// Getter: Returns a pointer to a GridSpace given its SpaceName.
GridSpace* Grid::getSpace(SpaceName space_name) const {
    return this->grid[static_cast<size_t>(space_name) - 1]; // Adjust for 0-indexing.
}

// Getter: Returns a pointer to a GridSpace given its string representation.
GridSpace* Grid::getSpace(string space_string) const {
    return this->getSpace(Spaces::nameFromString(space_string));
}

// Getter: Returns a pointer to a GridSpace given its column and row.
GridSpace* Grid::getSpace(Column column, Row row) const {
    return this->getSpace(static_cast<int>(column) - 64, static_cast<int>(row)); // Convert column letter to index.
}

// Getter: Returns a pointer to a GridSpace given its column and row numbers.
GridSpace* Grid::getSpace(int column_number, int row_number) const {
    int index = (column_number - 1) * 10; // Calculate index based on column and row.
    index += (row_number - 1);
    return this->grid[index];
}

// Method: Checks if a space is in the "no-go" list using its SpaceName.
bool Grid::isNoGoSpace(SpaceName space_name) const {
    for(SpaceName space : this->noGoSpaces)
        if(space_name == space)
            return true;
    return false;
}

// Method: Checks if a space is in the "no-go" list using its string representation.
bool Grid::isNoGoSpace(string space_string) const {
    return this->isNoGoSpace(Spaces::nameFromString(space_string));
}

// Method: Checks if any of the given spaces are in the "no-go" list.
bool Grid::hasNoGoSpace(vector<string> space_strings) const {
    for(string space_string : space_strings)
        if(this->isNoGoSpace(space_string))
            return true;
    return false;
}

// Method: Gets the space string north of the given space string.
string Grid::N(string start) {
    char letter = start.at(0);
    char number = start.length() == 3 ? '0' : start.at(1); // Handle '10' as a special case.
    if (number == '1')
        throw out_of_range("Cannot go North from first row."); // Throw exception if at the top row.
    char& new_number = number;
    if(new_number == '0')
        new_number = '9'; // Change '0' (representing 10) to '9'.
    else new_number = static_cast<char>(number - 1); // Decrease row number.
    string new_space = "";
    new_space += letter;
    new_space += number;
    return new_space;
}

// Method: Gets the space string south of the given space string.
string Grid::S(string start) {
    char letter = start.at(0);
    char number = start.length() == 3 ? '0' : start.at(1); // Handle '10' as a special case.
    if (number == '0')
        throw out_of_range("Cannot go South from last row."); // Throw exception if at the bottom row.
    char& new_number = number;
    if(new_number == '9')
        new_number = '0'; // Change '9' to '0' for the next row.
    else new_number = static_cast<char>(number + 1); // Increase row number.
    string new_space = "";
    new_space += letter;
    if(new_number == '0')
        new_space += "10"; // Add '10' for row 10.
    else new_space += number;
    return new_space;
}

// Method: Gets the space string east of the given space string.
string Grid::E(string start) {
    char letter = start.at(0);
    char number = start.length() == 3 ? '0' : start.at(1); // Handle '10' as a special case.
    if (letter == 'J')
        throw out_of_range("Cannot go East from last column."); // Throw exception if at the rightmost column.
    char& new_letter = letter;
    new_letter = static_cast<char>(letter + 1); // Move to the next column.
    string new_space = "";
    new_space += letter;
    if(number == '0')
        new_space += "10"; // Add '10' for row 10.
    else new_space += number;
    return new_space;
}

// Method: Gets the space string west of the given space string.
string Grid::W(string start) {
    char letter = start.at(0);
    char number = start.length() == 3 ? '0' : start.at(1); // Handle '10' as a special case.
    if (letter == 'A')
        throw out_of_range("Cannot go West from first column."); // Throw exception if at the leftmost column.
    char& new_letter = letter;
    new_letter = static_cast<char>(letter - 1); // Move to the previous column.
    string new_space = "";
    new_space += letter;
    if(number == '0')
        new_space += "10"; // Add '10' for row 10.
    else new_space += number;
    return new_space;
}

// Method: Returns a new space string after moving in the specified direction from a starting space.
string Grid::goDirection(string start, char direction) {
    switch(direction) {
        case 'N': return N(start);
        case 'S': return S(start);
        case 'E': return E(start);
        case 'W': return W(start);
        default: throw invalid_argument("Bad direction."); // Throw exception for invalid direction.
    }
}

// Method: Generates a vector of space strings in a specified direction and length.
vector<string> Grid::getVector(string start, char direction, int length, bool include_start) {
    vector<string> the_vector;
    if (include_start)
        the_vector.push_back(start); // Include starting space if requested.
    string prev = start;
    for(int i = 0; i < length; i++) {
        string& cur = prev;
        cur = goDirection(prev, direction); // Move to the next space in the specified direction.
        the_vector.push_back(cur);
    }
    return the_vector;
}

// Method: Returns a vector of neighboring space strings for a given space string.
vector<string> Grid::neighborSpaces(string space_string) {
    vector<string> neighbors;
    char directions[] = {'N', 'S', 'E', 'W'}; // Possible directions.
    for(char direction : directions) {
        try {
            neighbors.push_back(goDirection(space_string, direction)); // Try to get the neighboring space.
        } catch(out_of_range e) {
            continue; // Skip if out of bounds.
        }
    }
    return neighbors;
}

// Method: Returns a vector of neighboring space strings for multiple space strings.
vector<string> Grid::neighborSpaces(vector<string> space_strings) {
    vector<string> neighbors;
    if(space_strings.size() == 1)
        return neighborSpaces(space_strings[0]); // Return single space neighbors if only one space is provided.
    for(size_t i = 0; i < space_strings.size(); i++) {
        vector<string> neighbor_spaces = neighborSpaces(space_strings[i]);
        if(i == 0 || i == (space_strings.size())) {
            if(i == 0)
                for(string neighbor_space : neighbor_spaces)
                    if(neighbor_space != space_strings[1])
                        neighbors.push_back(neighbor_space); // Exclude immediate neighbor.
            else
                for(string neighbor_space : neighbor_spaces)
                    if(neighbor_space != space_strings[i - 1])
                        neighbors.push_back(neighbor_space); // Exclude previous space.
        } else
            for(string neighbor_space : neighbor_spaces)
                if(neighbor_space != space_strings[i - 1] && neighbor_space != space_strings[i + 1])
                    neighbors.push_back(neighbor_space); // Exclude both adjacent spaces.
    }
    return neighbors;
}

// Method: Places a stud on a specific space in the grid.
void Grid::setOnSpace(string space, Stud* stud) const {
    GridSpace* gspace = this->getSpace(space); // Get the space on the grid.
    gspace->addStud(stud); // Add the stud to the space.
    stud->setOnSpace(gspace->getSpaceName()); // Associate the space with the stud.
}

// Method: Targets a specific space on the grid and returns the result.
TargetResult Grid::target(string space_string) const {
    return this->getSpace(space_string)->target(); // Call the target method on the GridSpace.
}

// Method: Displays the grid, optionally showing hidden details for Camden (CPU).
void Grid::showGrid(bool show_camden) const {
    cout << "      A B C D E F G H I J\n"; // Print column headers.
    cout << "" << endl;
    for(int i = 0; i < 10; i++) {
        if (i == 9)
            cout << (i + 1); // Print row number for the 10th row.
        else
            cout << " " << (i + 1); // Print row number with leading space.
        cout << "    ";
        for(int j = 0; j < 10; j++)
            if(show_camden && this->ofPlayer == CPU)
                cout << this->getSpace(i + 1, j + 1)->getPrimeLabel() << " "; // Show hidden details if Camden's grid.
            else cout << this->getSpace(i + 1, j + 1)->getLabel() << " "; // Show normal label otherwise.
        cout << "\n"; // Move to the next line after each row.
    }
}
