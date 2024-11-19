#include <string>      // Provides the string class.
    using std::string;

#include <stdexcept>   // Provides standard exceptions like invalid_argument.
    using std::invalid_argument;

#include "Enums.h"     // Includes enumerations such as SpaceName, Column, and Row.

// Checks if a given string is a valid space string.
bool Spaces::isSpaceString(string space_string) {
    for (string a_space_string : spaceStrings) { // Iterates over the list of valid space strings.
        if (space_string == a_space_string)     // Compares input with each valid string.
            return true;                        // Returns true if a match is found.
    }
    return false;                               // Returns false if no match is found.
}

// Converts a space string to its corresponding SpaceName.
SpaceName Spaces::nameFromString(string space_string) {
    for (size_t i = 0; i < 100; i++) {                  // Iterates through all space strings.
        if (spaceStrings[i] == space_string)           // Finds the matching space string.
            return spaceNames[i];                      // Returns the corresponding SpaceName.
    }
    throw invalid_argument("Bad argument: " + space_string); // Throws an exception for invalid input.
}

// Converts a SpaceName to its corresponding string representation.
string Spaces::stringFromName(SpaceName space_name) {
    size_t space_name_int = static_cast<size_t>(space_name);  // Converts the SpaceName enum to an index.
    return spaceStrings[space_name_int - 1];                 // Returns the corresponding string.
}

// Converts a column character (e.g., 'A') to its corresponding Column enum.
Column Spaces::columnFromChar(char the_char) {
    for (size_t i = 0; i < 10; i++) {                // Iterates through all column characters.
        if (columnChars[i] == the_char)             // Finds the matching character.
            return columnNames[i];                  // Returns the corresponding Column enum.
    }
    throw invalid_argument("Bad argument: " + the_char); // Throws an exception for invalid input.
}

// Converts a row character (e.g., '1') to its corresponding Row enum.
Row Spaces::rowFromChar(char the_char) {
    for (size_t i = 0; i < 10; i++) {               // Iterates through all row characters.
        if (rowChars[i] == the_char)               // Finds the matching character.
            return rowNames[i];                    // Returns the corresponding Row enum.
    }
    throw invalid_argument("Bad argument: " + the_char); // Throws an exception for invalid input.
}

// Converts a Column enum to its corresponding character (e.g., 'A').
char Spaces::charFromColumn(Column the_column) {
    return columnChars[static_cast<size_t>(static_cast<char>(the_column) - 65)]; 
    // Converts the Column enum to an index and retrieves the corresponding character.
}

// Converts a Row enum to its corresponding character (e.g., '1').
char Spaces::charFromRow(Row the_row) {
    return rowChars[static_cast<size_t>(the_row) - 1]; // Converts the Row enum to an index and retrieves the corresponding character.
}
