#ifndef ENUMS_H
#define ENUMS_H

#include <string>  // Provides the string class.
    using std::string;

// **ENUMERATIONS**

// Represents the status of a grid space (untargeted or targeted).
enum SpaceStatus { UNTARGETED, TARGETED };

// Represents the status of a stud on a ship (intact or compromised).
enum StudStatus { INTACT, COMPROMISED };

// Represents the overall status of a ship (afloat or sunken).
enum ShipStatus { AFLOAT, SUNKEN };

// Represents the specific name of a stud on ships.
enum StudName { 
    A_1, A_2, A_3, A_4, A_5, 
    B_1, B_2, B_3, B_4, 
    D_1, D_2, D_3, 
    S_1, S_2, S_3, 
    C_1, C_2 
};

// Represents columns on the grid using phonetic alphabet.
enum Column { 
    ALPHA = 'A', BRAVO, CHARLIE, DELTA, ECHO, FOXTROT, GULF, INDIA, JULIET 
};

// Represents rows on the grid as numbers.
enum Row { 
    ONE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN 
};

// Represents the type of ship.
enum ShipType { CARRIER, BATTLESHIP, SUBMARINE, DESTROYER, CRUISER };

// Represents difficulty levels for a player type.
enum CamdenType { EASY, HARD };

// Represents the result of an attack (miss or hit).
enum TargetResult { MISS, HIT };

// Represents the type of player (CPU or human).
enum PlayerType { CPU, MAN };

// Represents names for every space on a 10x10 grid.
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
    A10, B10, C10, D10, E10, F10, G10, H10, I10, J10
};

// **STRUCTURES**

// Handles spaces on the game grid.
struct Spaces {
    // Arrays representing grid spaces and attributes.
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
        A10, B10, C10, D10, E10, F10, G10, H10, I10, J10
    };

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
        "A10", "B10", "C10", "D10", "E10", "F10", "G10", "H10", "I10", "J10"
    };

    inline static Column columnNames[] = { ALPHA, BRAVO, CHARLIE, DELTA, ECHO, FOXTROT, GULF, INDIA, JULIET };
    inline static Row rowNames[] = { ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN };
    inline static char columnChars[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };
    inline static char rowChars[] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };

    // Methods for validating and converting grid spaces and coordinates.
    static bool isSpaceString(string space_string);
    static SpaceName nameFromString(string space_string);
    static string stringFromName(SpaceName space_name);
    static Column columnFromChar(char the_char);
    static Row rowFromChar(char the_char);
    static char charFromColumn(Column the_column);
    static char charFromRow(Row the_row);
};

// Handles studs on ships.
struct Studs {
    inline static StudName studNames[] = { 
        A_1, A_2, A_3, A_4, A_5, 
        B_1, B_2, B_3, B_4, 
        D_1, D_2, D_3, 
        S_1, S_2, S_3, 
        C_1, C_2 
    };
};

#endif // Ends the include guard.
