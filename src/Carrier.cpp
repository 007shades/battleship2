#include "Carrier.h"
#include "Ship.h"
#include "Enums.h"
#include "Grid.h"
#include "Stud.h"

#include <string>
    using std::string;

#include <array>
    using std::array;

Carrier::Carrier() : Ship(ShipType::Carrier) {}

Carrier::Carrier(PlayerType of_player) : Ship(ShipType::Carrier, of_player) {}

Carrier::Carrier(Grid* on_grid) : Ship(ShipType::Carrier, on_grid) {}

Carrier::~Carrier() {
    for(size_t i = 0; i < 5; ++i) {
        delete this->studs[i];
        this->studs[i] = nullptr;
    }
}

array<Stud*, 5> Carrier::getStuds() const {
    return this->studs;
}

