#include <iostream>
#include "worker.h"
#include "simulation_context.h"
#include "tribe.h"

Worker::Worker(int id) : Unit(id) {}

void Worker::act(SimulationContext& context) {
    context.ownTribe.get().getStrategy().actWorker(*this, context);
}

void Worker::acceptAttack(UnitAttacker& attacker) {
    attacker.attackWorker(*this);
}