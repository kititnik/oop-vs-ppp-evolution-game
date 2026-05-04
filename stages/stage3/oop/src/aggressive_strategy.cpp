#include <iostream>
#include <optional>
#include "aggressive_strategy.h"
#include "simulation_context.h"
#include "tribe.h"
#include "warrior.h"
#include "worker.h"

void AggressiveStrategy::actWarrior(Warrior& unit, SimulationContext& context) {
    auto target = context.enemyTribe.get().getWeakestAliveUnit();
    if(target == std::nullopt) {
        std::cout << "Warrior " << unit.getId() << " didn't find enemy to attack\n";
        return;
    }
    target->get().acceptAttack(unit);
}

void AggressiveStrategy::actWorker(Worker& unit, SimulationContext& context) {
    (void)unit;
    (void)context;
}
