#include "Camden.h"

#include "Enums.h"
#include "Grid.h"
#include "Player.h"

#include <string>
    using std::string;

#include <vector>
    using std::vector;


bool Camden::did_just_sink_ship() const {
    return this->self->getFoe()->justSunkenShip() != nullptr;
}

void Camden::set_Camden() {
    for(string space : Spaces::spaceStrings)
        this->availableSpaces.push_back(space);
    for(char direction : this->directions)
        this->attackDirections.push_back(direction);
}