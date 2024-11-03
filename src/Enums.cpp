#include <string> // Include string for handling text.
    using std::string; // Use string from the standard namespace.

#include <stdexcept> // Include for handling exceptions like invalid_argument.
    using std::invalid_argument; // Use invalid_argument from the standard namespace.

#include "Enums.h" // Include Enums for enumerated types and related data.

// Method: Checks if a given space string is valid by comparing it with known space strings.
bool Spaces::isSpaceString(string space_string) {
    for(string a_space_string : spaceStrings) // Iterate through all known space strings.
        if(space_string == a_space_string) // Check if the input matches any of the known strings.
            return true; // Return true if a match is found.
    return false; // Return false if no match is found.
}

// Method: Converts a valid space string to its corresponding SpaceName.
SpaceName Spaces::nameFromString(string space_string) {
    for (size_t i = 0; i < 100; i++) { // Iterate through spaceStrings up to 100 elements.
        if (spaceStrings[i] == space_string) // Check if the input matches the current string.
            return spaceNames[i]; // Return the corresponding SpaceName.
    }
    throw invalid_argument("Bad argument: " + space_string); // Throw exception if no match is found.
}

// Method: Converts a SpaceName to its corresponding space string.
string Spaces::stringFromName(SpaceName space_name) {
    size_t space_name_int = static_cast<size_t>(space_name); // Convert SpaceName to an integer.
    return spaceStrings[space_name_int - 1]; // Return the corresponding space string (adjusted for 0-indexing).
}

// Method: Converts a character representing a column to its corresponding Column enumeration value.
Column Spaces::columnFromChar(char the_char) {
    for(size_t i = 0; i < 10; i++) { // Iterate through columnChars array.
        if (columnChars[i] == the_char) // Check if the input character matches.
            return columnNames[i]; // Return the corresponding Column.
    }
    throw invalid_argument("Bad argument: " + the_char); // Throw exception if no match is found.
}

// Method: Converts a character representing a row to its corresponding Row enumeration value.
Row Spaces::rowFromChar(char the_char) {
    for(size_t i = 0; i < 10; i++) { // Iterate through rowChars array.
        if (rowChars[i] == the_char) // Check if the input character matches.
            return rowNames[i]; // Return the corresponding Row.
    }
    throw invalid_argument("Bad argument: " + the_char); // Throw exception if no match is found.
}

// Method: Converts a Column enumeration value to its corresponding character representation.
char Spaces::charFromColumn(Column the_column) {
    return columnChars[static_cast<size_t>(static_cast<char>(the_column) - 65)]; // Convert Column to character and find its representation in columnChars.
}

// Method: Converts a Row enumeration value to its corresponding character representation.
char Spaces::charFromRow(Row the_row) {
    return rowChars[static_cast<size_t>(the_row) - 1]; // Convert Row to character index and find its representation in rowChars.
}
