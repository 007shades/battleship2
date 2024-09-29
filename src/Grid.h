#ifndef GRID_H
#define GRID_H

#include <array>
    using std::array;

#include <string>
    using std::string;

#include <vector>
    using std::vector;

#include "Enums.h"

#include "GridSpace.h"


class Grid {
    private:
        array<GridSpace*, 100> grid;
        PlayerType ofPlayer;
        vector<SpaceName> noGoSpaces;
        void populate_grid();
        void populate_grid(PlayerType of_player);

    public:
        Grid();
        explicit Grid(PlayerType of_player);
        ~Grid();
        
        array<GridSpace*, 100> getGrid() const;
        PlayerType getOfPlayer() const;
        vector<SpaceName> getNoGoSpaces() const;

        void setGrid(array<GridSpace*, 100> the_grid);
        void setOfPlayer(PlayerType of_player);
        void addNoGoSpace(SpaceName space);
        void addNoGoSpaces(vector<string> space_strings);

        GridSpace* getSpace(SpaceName space_name) const;
        GridSpace* getSpace(string space_string) const;
        GridSpace* getSpace(Column column, Row row) const;
        GridSpace* getSpace(int column_number, int row_number) const;
        
        bool isNoGoSpace(string space_string) const;
        bool isNoGoSpace(SpaceName space_name) const;
        bool hasNoGoSpace(vector<string> space_strings) const;

        static string N(string start);
        static string S(string start);
        static string E(string start);
        static string W(string start);
        static string goDirection(string start, char direction);
        static vector<string> getVector(string start, char direction, int length, bool include_start = true);
        
        static vector<string> neighborSpaces(string space_string);
        static vector<string> neighborSpaces(vector<string> space_strings);

        void setOnSpace(string space, Stud* stud) const;
        
        TargetResult target(string space_string) const;

        void showGrid(bool show_camden = false) const;
};

#endif