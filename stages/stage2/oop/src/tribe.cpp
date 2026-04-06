#include "tribe.h"
#include "simulation_context.h"
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <memory>
#include <optional>
#include <utility>
#include <vector>

Tribe::Tribe() = default;

void Tribe::addUnit(std::unique_ptr<Unit> unit) {
    _units.push_back(std::move(unit));
}

void Tribe::actAll(SimuationContext& context) {
    for (auto& unit : _units) {
        if(!unit->isAlive()) continue;
        unit->act(context);
    }
}

std::optional<std::reference_wrapper<Unit>> Tribe::getRandomAliveUnit() {
    size_t aliveCount = 0;
    for (auto& unit : _units) {
        if(unit->isAlive()) {
            aliveCount++;
        }
    }
    if(aliveCount == 0) return std::nullopt;

    size_t target = rand() % aliveCount;
    for (auto& unit : _units) {
        if(unit->isAlive()) {
            if(target == 0) return *unit;
            target--;
        }
    }
    return std::nullopt;
}