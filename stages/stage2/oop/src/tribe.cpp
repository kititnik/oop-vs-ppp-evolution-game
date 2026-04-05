#include "tribe.h"
#include <utility>

Tribe::Tribe() = default;

void Tribe::addUnit(std::unique_ptr<Unit> unit) {
    _units.push_back(std::move(unit));
}

void Tribe::actAll() {
    for (auto& unit : _units) {
        unit->act();
    }
}