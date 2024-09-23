#include "Grid.h"

#include <array>
    using std::array;

#include <string>
    using std::string;
    using std::to_string;

#include <vector>
    using std::vector;

#include <stdexcept>
    using std::out_of_range;
    using std::invalid_argument;

#include "Enums.h"

#include "GridSpace.h"

void Grid::populate_grid() {
    for(size_t i = 0; i < 100; ++i)
        this->grid[i] = nullptr;
}

void Grid::populate_grid(PlayerType of_player) {
    for(size_t i = 0; i < 100; ++i)
        this->grid[i] = new GridSpace(Spaces::spaceNames[i], of_player);
}

Grid::Grid() {
    this->populate_grid();
}

Grid::Grid(PlayerType of_player) : ofPlayer {of_player} {
    this->populate_grid(of_player);
}

Grid::~Grid() {
    for(size_t i = 0; i < 100; i++) {
        delete this->grid[i];
        this->grid[i] = nullptr;
    }
}

array<GridSpace*, 100> Grid::getGrid() const {
    return this->grid;
}

PlayerType Grid::getOfPlayer() const {
    return this->ofPlayer;
}

vector<SpaceName> Grid::getNoGoSpaces() const {
    return this->noGoSpaces;
}

void Grid::setGrid(array<GridSpace*, 100> the_grid) {
    this->grid = the_grid;
}

void Grid::setOfPlayer(PlayerType of_player) {
    this->ofPlayer = of_player;
}

void Grid::addNoGoSpace(SpaceName space) {
    if(!this->isNoGoSpace(space))
        this->noGoSpaces.push_back(space);
}

void Grid::addNoGoSpaces(vector<string> space_strings) {
    for(string space_string : space_strings)
        if(this->isNoGoSpace(space_string))
            this->addNoGoSpace(Spaces::nameFromString(space_string));
}

GridSpace* Grid::getSpace(SpaceName space_name) const {
    return this->grid [static_cast<size_t> (space_name) - 1];
}

GridSpace* Grid::getSpace(string space_string) const {
    return this->getSpace(Spaces::nameFromString(space_string));
}

GridSpace* Grid::getSpace(Column column, Row row) const {
    return this->getSpace(static_cast<int>(column) - 64, static_cast<int>(row));
}

GridSpace* Grid::getSpace(int column_number, int row_number) const {
    int index = (column_number - 1) * 10;
    index += (row_number - 1);
    return this->grid[index];
}

bool Grid::isNoGoSpace(SpaceName space_name) const {
    for(SpaceName space : this->noGoSpaces)
        if(space_name == space)
            return true;
    return false;
}

bool Grid::isNoGoSpace(string space_string) const {
    return this->isNoGoSpace(Spaces::nameFromString(space_string));
}

bool Grid::hasNoGoSpace(vector<string> space_strings) const {
    for(string space_string : space_strings)
        if(this->isNoGoSpace(space_string))
            return true;
    return false;
}

string Grid::N(string start) {
    char letter = start.at(0);
    char number = start.length() == 3 ? '0' : start.at(1);
    if (number == '1')
        throw out_of_range("Cannot go North from first row.");
    char& new_number = number;
    if(new_number == '0')
        new_number = '9';
    else new_number = static_cast<char>(number - 1);
    string new_space = "";
    new_space  += letter;
    new_space += number;
    return new_space;
}

string Grid::S(string start) {
    char letter = start.at(0);
    char number = start.length() == 3 ? '0' : start.at(1);
    if (number == '0')
        throw out_of_range("Cannot go South from last row.");
    char& new_number = number;
    if(new_number == '9')
        new_number = '0';
    else new_number = static_cast<char>(number + 1);
    string new_space = "";
    new_space  += letter;
    if(new_number == '0')
        new_space += "10";
    else new_space += number;
    return new_space;
}

string Grid::E(string start) {
    char letter = start.at(0);
    char number = start.length() == 3 ? '0' : start.at(1);
    if (letter == 'J')
        throw out_of_range("Cannot go East from last column.");
    char& new_letter = letter;
    new_letter = static_cast<char>(letter + 1);
    string new_space = "";
    new_space  += letter;
    if(number == '0')
        new_space += "10";
    else new_space += number;
    return new_space;
}

string Grid::W(string start) {
    char letter = start.at(0);
    char number = start.length() == 3 ? '0' : start.at(1);
    if (letter == 'A')
        throw out_of_range("Cannot go West from first column.");
    char& new_letter = letter;
    new_letter = static_cast<char>(letter - 1);
    string new_space = "";
    new_space  += letter;
    if(number == '0')
        new_space += "10";
    else new_space += number;
    return new_space;
}

string Grid::goDirection(string start, char direction) {
    switch(direction) {
        case 'N': return N(start);
        case 'S': return S(start);
        case 'E': return E(start);
        case 'W': return W(start);
        default: throw invalid_argument("Bad direction.");
    }
}

vector<string> Grid::getVector(string start, char direction, int length, bool include_start) {
    vector<string> the_vector;
    if (include_start)
        the_vector.push_back(start);
    string prev = start;
    for(int i=0; i<length; i++) {
        string& cur = prev;
        cur = goDirection(prev, direction);
        the_vector.push_back(cur);
    }
    return the_vector;
}

vector<string> Grid::neighborSpaces(string space_string) {
    vector<string> neighbors;
    char directions[] = {'N', 'S', 'E', 'W'};
    for(char direction : directions) {
        try {
            neighbors.push_back(goDirection(space_string, direction));
        } catch(out_of_range e) {
            continue;
        }
    }
    return neighbors;
}

vector<string> Grid::neighborSpaces(vector<string> space_strings) {
    vector<string> neighbors;
    if(space_strings.size() == 1)
        return neighborSpaces(space_strings[0]);
    for(size_t i = 0; i < space_strings.size(); ++i) {
        vector<string> neighbor_spaces = neighborSpaces(space_strings[i]);
        if(!i || i == (space_strings.size() - 1)) {
            if(!i)
                for(string neighbor_space : neighbor_spaces)
                    if(neighbor_space != space_strings[1])
                        neighbors.push_back(neighbor_space);
            else
                for(string neighbor_space : neighbor_spaces)
                    if(neighbor_space != space_strings[i-1])
                        neighbors.push_back(neighbor_space);
        } else 
            for(string neighbor_space : neighbor_spaces)
                if(neighbor_space != space_strings[i - 1] && neighbor_space != space_strings[i + 1])
                    neighbors.push_back(neighbor_space);
    }
}

TargetResult Grid::target(string space_string) const {
    return this->getSpace(space_string)->target();
}