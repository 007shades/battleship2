#ifndef ENUMS_H // Include guard to prevent multiple inclusions.
#define ENUMS_H

#include <string> // Include for using the string class.
    using std::string; // Use string from the standard namespace.

// Enumeration representing the status of a space on the game grid.
enum SpaceStatus {UNTARGETED, TARGETED}; // UNTARGETED means not hit, TARGETED means hit.

// Enumeration representing the status of a stud (part of a ship).
enum StudStatus {INTACT, COMPROMISED}; // INTACT means undamaged, COMPROMISED means damaged.

// Enumeration representing the status of a ship.
enum ShipStatus {AFLOAT, SUNKEN}; // AFLOAT means not sunk, SUNKEN means fully compromised.

// Enumeration representing the names of individual studs.
enum StudName {A_1, A_2, A_3, A_4, A_5, B_1, B_2, B_3, B_4, D_1, D_2, D_3, S_1, S_2, S_3, C_1, C_2}; // Various names of ship parts.

// Enumeration representing the columns of the grid.
enum Column {ALPHA = 'A', BRAVO, CHARLIE, DELTA, ECHO, FOXTROT, GULF, INDIA, JULIET}; // Column names using military phonetic alphabet.

// Enumeration representing the rows of the grid.
enum Row {ONE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN}; // Row numbers from 1 to 10.

// Enumeration representing the types of ships in the game.
enum ShipType {CARRIER, BATTLESHIP, SUBMARINE, DESTROYER, CRUISER}; // Different types of ships.

// Enumeration representing the levels of difficulty for Camden's AI.
enum CamdenType {EASY, HARD}; // EASY and HARD difficulty levels.

// Enumeration representing the result of targeting a space.
enum TargetResult {MISS, HIT}; // MISS means no ship hit, HIT means a ship was hit.

// Enumeration representing the type of player.
enum PlayerType {CPU, MAN}; // CPU for computer-controlled, MAN for human player.

// Enumeration representing the names of spaces on the grid.
enum SpaceName {
    A1 = 1, B1, C1, D1, E1, F1, G1, H1, I1, J1,
    A2, B2, C2, D2, E2, F2, G2, H2, I2, J2,
    A3, B3, C3, D3, E3, F3, G3, H3, I3, J3,
    A4, B4, C4, D4, E4, F4, G4, H4, I4, J4,
    A5, B5, C5, D5, E5, F5, G5, H5, I5, J5,
    A6, B6, C6, D6, E6, F6, G6, H6, I6, J6,
    A7, B7, C7, D7, E7, F7, G7, H7, I7, J7,
    A8, B8, C8, D8, E8, F8, G8, H8, I8, J8,
    A9, B9, C9, D9, E9, F9, G9, H9, I9, J9,
    A10, B10, C10, D10, E10, F10, G10, H10, I10, J10 // Spaces from A1 to J10.
};

// Struct containing static members related to space properties and conversions.
struct Spaces {
    // Static array mapping SpaceName enumerators.
    inline static SpaceName spaceNames[] = {
        A1, B1, C1, D1, E1, F1, G1, H1, I1, J1,
        A2, B2, C2, D2, E2, F2, G2, H2, I2, J2,
        A3, B3, C3, D3, E3, F3, G3, H3, I3, J3,
        A4, B4, C4, D4, E4, F4, G4, H4, I4, J4,
        A5, B5, C5, D5, E5, F5, G5, H5, I5, J5,
        A6, B6, C6, D6, E6, F6, G6, H6, I6, J6,
        A7, B7, C7, D7, E7, F7, G7, H7, I7, J7,
        A8, B8, C8, D8, E8, F8, G8, H8, I8, J8,
        A9, B9, C9, D9, E9, F9, G9, H9, I9, J9,
        A10, B10, C10, D10, E10, F10, G10, H10, I10, J10 // Full grid of space names.
    };

    // Static array mapping space names to string representations.
    inline static string spaceStrings[] = {
        "A1", "B1", "C1", "D1", "E1", "F1", "G1", "H1", "I1", "J1",
        "A2", "B2", "C2", "D2", "E2", "F2", "G2", "H2", "I2", "J2",
        "A3", "B3", "C3", "D3", "E3", "F3", "G3", "H3", "I3", "J3",
        "A4", "B4", "C4", "D4", "E4", "F4", "G4", "H4", "I4", "J4",
        "A5", "B5", "C5", "D5", "E5", "F5", "G5", "H5", "I5", "J5",
        "A6", "B6", "C6", "D6", "E6", "F6", "G6", "H6", "I6", "J6",
        "A7", "B7", "C7", "D7", "E7", "F7", "G7", "H7", "I7", "J7",
        "A8", "B8", "C8", "D8", "E8", "F8", "G8", "H8", "I8", "J8",
        "A9", "B9", "C9", "D9", "E9", "F9", "G9", "H9", "I9", "J9",
        "A10", "B10", "C10", "D10", "E10", "F10", "G10", "H10", "I10", "J10" // String representations of space names.
    };

    // Static arrays for column and row data.
    inline static Column columnNames[] = {ALPHA, BRAVO, CHARLIE, DELTA, ECHO, FOXTROT, GULF, INDIA, JULIET}; // Columns A to J.
    inline static Row rowNames[] = {ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN}; // Rows 1 to 10.
    inline static char columnChars[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'}; // Characters representing columns.
    inline static char rowChars[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'}; // Characters representing rows (0 represents 10).

    // Static methods for conversions and checks.
    static bool isSpaceString(string space_string); // Checks if a string represents a valid space.
    static SpaceName nameFromString(string space_string); // Converts a string to a SpaceName.
    static string stringFromName(SpaceName space_name); // Converts a SpaceName to a string.
    static Column columnFromChar(char the_char); // Converts a character to a Column.
    static Row rowFromChar(char the_char); // Converts a character to a Row.
    static char charFromColumn(Column the_column); // Converts a Column to a character.
    static char charFromRow(Row the_row); // Converts a Row to a character.
};

// Struct containing static members related to stud properties.
struct Studs {
    inline static StudName studNames[] = {A_1, A_2, A_3, A_4, A_5, B_1, B_2, B_3, B_4, D_1, D_2, D_3, S_1, S_2, S_3, C_1, C_2}; // Array of stud names.
};

#endif // End of include guard.
