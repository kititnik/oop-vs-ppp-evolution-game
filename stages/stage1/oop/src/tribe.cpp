#include "tribe.h"

Tribe::Tribe(int unitCount) {
    for (int i = 0; i < unitCount; ++i) {
        _units.push_back(Unit(i));
    }
}

void Tribe::actAll() {
    for (auto& unit : _units) {
        unit.act();
    }
}