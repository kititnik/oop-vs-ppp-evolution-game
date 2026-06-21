#include <cstdlib>
#include <iostream>
#include <optional>
#include "random_strategy.h"
#include "simulation_context.h"
#include "tribe.h"
#include "warrior.h"
#include "worker.h"

void RandomStrategy::actWarrior(Warrior& unit, SimulationContext& context) {
    auto target = context.enemyTribe.get().getRandomAliveUnit();
    if(target == std::nullopt) {
        std::cout << "Warrior " << unit.getId() << " didn't find enemy to attack\n";
        return;
    }
    target->get().acceptAttack(unit);
}

void RandomStrategy::actWorker(Worker& unit, SimulationContext& context) {
    int foundResources = rand() % 10;
    auto& ownTribe = context.ownTribe.get();
    ownTribe.setResourcesCount(foundResources + ownTribe.getResourcesCount());
    std::cout << "Worker " << unit.getId() << " found: " << foundResources << "; now have " << ownTribe.getResourcesCount() << "\n";
}
