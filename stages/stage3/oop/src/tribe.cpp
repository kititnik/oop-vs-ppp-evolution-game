#include "tribe.h"
#include "simulation_context.h"
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <memory>
#include <optional>
#include <utility>
#include <vector>

Tribe::Tribe(std::unique_ptr<TribeFactory> factory, std::unique_ptr<BattleStrategy> strategy) 
    : _factory(std::move(factory)), _strategy(std::move(strategy)) {
    _resourcesCount = 0;
}

void Tribe::addUnit(std::unique_ptr<Unit> unit) {
    _units.push_back(std::move(unit));
}

void Tribe::actAll(SimulationContext& context) {
    for (auto& unit : _units) {
        if(!unit->isAlive()) continue;
        unit->act(context);
    }
}

void Tribe::createUnits(int count, int idOffset) {
    for (int i = 0; i < count; ++i) {
        addUnit(_factory->createUnit(idOffset + i));
    }
}

std::optional<std::reference_wrapper<Unit>> Tribe::getRandomAliveUnit() {
    // Two passes: first we count the live ones, then we go to the desired one.
    // Does not require an additional buffer.
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

std::optional<std::reference_wrapper<Unit>> Tribe::getWeakestAliveUnit() {
    Unit* weakest = nullptr;
    int minHealth = INT_MAX;
    for (auto& unit : _units) {
        if(unit->isAlive() && unit->getHealth() < minHealth) {
            minHealth = unit->getHealth();
            weakest = unit.get();
        }
    }
    if(weakest == nullptr) return std::nullopt;
    return *weakest;
}

int Tribe::getResourcesCount() {
    return _resourcesCount;
}

void Tribe::setResourcesCount(int resources) {
    _resourcesCount = std::max(resources, 0);
}

BattleStrategy& Tribe::getStrategy() {
    return *_strategy;
}