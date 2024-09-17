#include <string>
    using std::string;

#include <stdexcept>
    using std::invalid_argument;

#include "Enums.h"

SpaceName Spaces::nameFromString(string space_string) {
    for(size_t i = 0; i < 100; i ++) {
        if (spaceStrings[i] == space_string)
            return spaceNames[i];
    }
    throw invalid_argument("Bad argument: " + space_string);
}

string Spaces::stringFromName(SpaceName space_name) {
    size_t space_name_int = static_cast<size_t>(space_name);
    return spaceStrings[space_name_int];
}