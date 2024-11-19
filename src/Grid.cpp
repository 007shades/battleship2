#include "Grid.h"      // Includes the Grid class header file.

#include <array>       // Provides the array container class.
    using std::array;

#include <string>      // Provides the string class.
    using std::string;
    using std::to_string;

#include <vector>      // Provides the vector container class.
    using std::vector;

#include <stdexcept>   // Provides standard exceptions like out_of_range and invalid_argument.
    using std::out_of_range;
    using std::invalid_argument;

#include <iostream>    // Provides input/output utilities.
    using std::cout;
    using std::endl;

#include "Enums.h"     // Includes game-related enumerations.
#include "GridSpace.h" // Includes the GridSpace class for individual grid spaces.

// ** PRIVATE HELPERS **

// Populates the grid with nullptr values.
void Grid::populate_grid() {
    for (size_t i = 0; i < 100; ++i)
        this->grid[i] = nullptr;
}

// Populates the grid with new GridSpace objects for a specific player.
void Grid::populate_grid(PlayerType of_player) {
    for (size_t i = 0; i < 100; ++i)
        this->grid[i] = new GridSpace(Spaces::spaceNames[i], of_player);
}

// ** CONSTRUCTORS AND DESTRUCTOR **

// Default constructor initializes an empty grid.
Grid::Grid() {
    this->populate_grid();
}

// Constructor initializes a grid for a specific player.
Grid::Grid(PlayerType of_player) : ofPlayer {of_player} {
    this->populate_grid(of_player);
}

// Destructor cleans up dynamically allocated GridSpace objects.
Grid::~Grid() {
    for (size_t i = 0; i < 100; i++) {
        delete this->grid[i];
        this->grid[i] = nullptr;
    }
}

// ** GETTERS AND SETTERS **

// Returns the array of GridSpace pointers.
array<GridSpace*, 100> Grid::getGrid() const {
    return this->grid;
}

// Returns the player associated with this grid.
PlayerType Grid::getOfPlayer() const {
    return this->ofPlayer;
}

// Returns the list of "no-go" spaces.
vector<SpaceName> Grid::getNoGoSpaces() const {
    return this->noGoSpaces;
}

// Sets the grid with a new array of GridSpace pointers.
void Grid::setGrid(array<GridSpace*, 100> the_grid) {
    this->grid = the_grid;
}

// Sets the player associated with this grid.
void Grid::setOfPlayer(PlayerType of_player) {
    this->ofPlayer = of_player;
}

// Adds a space to the "no-go" list.
void Grid::addNoGoSpace(SpaceName space) {
    if (!this->isNoGoSpace(space))
        this->noGoSpaces.push_back(space);
}

// Adds multiple spaces to the "no-go" list using their string representations.
void Grid::addNoGoSpaces(vector<string> space_strings) {
    for (string space_string : space_strings)
        this->addNoGoSpace(Spaces::nameFromString(space_string));
}

// ** GRID SPACE OPERATIONS **

// Retrieves a specific GridSpace by SpaceName.
GridSpace* Grid::getSpace(SpaceName space_name) const {
    return this->grid[static_cast<size_t>(space_name) - 1];
}

// Retrieves a specific GridSpace by its string representation.
GridSpace* Grid::getSpace(string space_string) const {
    return this->getSpace(Spaces::nameFromString(space_string));
}

// Retrieves a specific GridSpace by column and row.
GridSpace* Grid::getSpace(Column column, Row row) const {
    return this->getSpace(static_cast<int>(column) - 64, static_cast<int>(row));
}

// Retrieves a specific GridSpace by column and row numbers.
GridSpace* Grid::getSpace(int column_number, int row_number) const {
    int index = (column_number - 1) * 10 + (row_number - 1);
    return this->grid[index];
}

// ** "NO-GO" SPACE CHECKS **

// Checks if a space is in the "no-go" list by SpaceName.
bool Grid::isNoGoSpace(SpaceName space_name) const {
    for (SpaceName space : this->noGoSpaces)
        if (space_name == space)
            return true;
    return false;
}

// Checks if a space is in the "no-go" list by its string representation.
bool Grid::isNoGoSpace(string space_string) const {
    return this->isNoGoSpace(Spaces::nameFromString(space_string));
}

// Checks if any of the given spaces are in the "no-go" list.
bool Grid::hasNoGoSpace(vector<string> space_strings) const {
    for (string space_string : space_strings)
        if (this->isNoGoSpace(space_string))
            return true;
    return false;
}

// ** GRID MOVEMENT FUNCTIONS **

// Moves north from a starting space.
string Grid::N(string start) {
    char letter = start.at(0);
    char number = start.length() == 3 ? '0' : start.at(1);
    if (number == '1')
        throw out_of_range("Cannot go North from first row.");
    char& new_number = number;
    new_number = (new_number == '0') ? '9' : static_cast<char>(number - 1);
    return string(1, letter) + new_number;
}

// Moves south from a starting space.
string Grid::S(string start) {
    char letter = start.at(0);
    char number = start.length() == 3 ? '0' : start.at(1);
    if (number == '0')
        throw out_of_range("Cannot go South from last row.");
    char& new_number = number;
    new_number = (new_number == '9') ? '0' : static_cast<char>(number + 1);
    return string(1, letter) + ((new_number == '0') ? "10" : string(1, new_number));
}

// Moves east from a starting space.
string Grid::E(string start) {
    char letter = start.at(0);
    if (letter == 'J')
        throw out_of_range("Cannot go East from last column.");
    return string(1, static_cast<char>(letter + 1)) + start.substr(1);
}

// Moves west from a starting space.
string Grid::W(string start) {
    char letter = start.at(0);
    if (letter == 'A')
        throw out_of_range("Cannot go West from first column.");
    return string(1, static_cast<char>(letter - 1)) + start.substr(1);
}

// Moves in a specified direction.
string Grid::goDirection(string start, char direction) {
    switch (direction) {
        case 'N': return N(start);
        case 'S': return S(start);
        case 'E': return E(start);
        case 'W': return W(start);
        default: throw invalid_argument("Bad direction.");
    }
}

// ** NEIGHBOR AND VECTOR OPERATIONS **

// Returns a vector of spaces in a direction from a starting space.
vector<string> Grid::getVector(string start, char direction, int length, bool include_start) {
    vector<string> the_vector;
    if (include_start)
        the_vector.push_back(start);
    string prev = start;
    for (int i = 0; i < length; i++) {
        prev = goDirection(prev, direction);
        the_vector.push_back(prev);
    }
    return the_vector;
}

// Returns the neighbors of a single space.
vector<string> Grid::neighborSpaces(string space_string) {
    vector<string> neighbors;
    char directions[] = {'N', 'S', 'E', 'W'};
    for (char direction : directions) {
        try {
            neighbors.push_back(goDirection(space_string, direction));
        } catch (out_of_range&) {
            continue;
        }
    }
    return neighbors;
}

// Returns the neighbors of a list of spaces.
vector<string> Grid::neighborSpaces(vector<string> space_strings) {
    vector<string> neighbors;
    if (space_strings.size() == 1)
        return neighborSpaces(space_strings[0]);
    for (size_t i = 0; i < space_strings.size(); i++) {
        vector<string> neighbor_spaces = neighborSpaces(space_strings[i]);
        if (i == 0 || i == (space_strings.size() - 1)) {
            for (string neighbor_space : neighbor_spaces)
                if ((i == 0 && neighbor_space != space_strings[1]) || 
                    (i == space_strings.size() - 1 && neighbor_space != space_strings[i - 1]))
                    neighbors.push_back(neighbor_space);
        } else {
            for (string neighbor_space : neighbor_spaces)
                if (neighbor_space != space_strings[i - 1] && neighbor_space != space_strings[i + 1])
                    neighbors.push_back(neighbor_space);
        }
    }
    return neighbors;
}

// ** SPACE OPERATIONS **

// Adds a stud to a specific space.
void Grid::setOnSpace(string space, Stud* stud) const {
    GridSpace* gspace = this->getSpace(space);
    gspace->addStud(stud);
    stud->setOnSpace(gspace->getSpaceName());
}

// Targets a space and returns the result (hit or miss).
TargetResult Grid::target(string space_string) const {
    return this->getSpace(space_string)->target();
}

// ** GRID DISPLAY **

// Displays the grid, optionally showing Camden's grid.
void Grid::showGrid(bool show_camden) const {
    cout << "      A B C D E F G H I J\n\n";
    for (int i = 0; i < 10; i++) {
        if (i == 9)
            cout << (i + 1);
        else
            cout << " " << (i + 1);
        cout << "    ";
        for (int j = 0; j < 10; j++) {
            if (show_camden && this->ofPlayer == CPU)
                cout << this->getSpace(j + 1, i + 1)->getPrimeLabel() << " ";
            else
                cout << this->getSpace(j + 1, i + 1)->getLabel() << " ";
        }
        cout << "\n";
    }
}
