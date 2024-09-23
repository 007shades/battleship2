#include <string>
    using std::string;

#include <stdexcept>
    using std::invalid_argument;

#include "Enums.h"

SpaceName Spaces::nameFromString(string space_string) {
    for (size_t i = 0; i < 100; i ++) {
        if (spaceStrings[i] == space_string)
            return spaceNames[i];
    }
    throw invalid_argument("Bad argument: " + space_string);
}

string Spaces::stringFromName(SpaceName space_name) {
    size_t space_name_int = static_cast<size_t>(space_name);
    return spaceStrings[space_name_int];
}

Column Spaces::columnFromChar(char the_char) {
    for(size_t i = 0; i < 10; i ++)
        if (columnChars[i] == the_char)
            return columnNames[i];
    throw invalid_argument("Bad argument: " + the_char);
}

Row Spaces::rowFromChar(char the_char) {
    for(size_t i = 0; i < 10; i ++)
        if (rowChars[i] == the_char)
            return rowNames[i];
    throw invalid_argument("Bad argument: " + the_char);
}

char Spaces::charFromColumn(Column the_column) {
    return columnChars [static_cast<size_t>(static_cast<char>(the_column) - 65)];
}

char Spaces::charFromRow(Row the_row) {
    return rowChars [static_cast<size_t>(the_row) - 1];
}