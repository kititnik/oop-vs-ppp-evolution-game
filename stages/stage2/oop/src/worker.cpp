#include <iostream>
#include "worker.h"
#include "simulation_context.h"
#include "tribe.h"

Worker::Worker(int id) : Unit(id) {}

void Worker::act(SimulationContext& context) {
    int foundResources = rand() % 10;
    auto& ownTribe = context.ownTribe.get();
    ownTribe.setResourcesCount(foundResources + ownTribe.getResourcesCount());
    std::cout << "Worker " << id << " found: " << foundResources << "; now have " << ownTribe.getResourcesCount() << "\n";
}

void Worker::acceptAttack(UnitAttacker& attacker) {
    attacker.attackWorker(*this);
}