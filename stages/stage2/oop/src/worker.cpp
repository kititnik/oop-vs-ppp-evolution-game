#include <iostream>
#include "worker.h"
#include "simulation_context.h"
#include "tribe.h"

Worker::Worker(int id) : Unit(id) {}

void Worker::act(SimuationContext& context) {
    int foundResources = rand() % 10;
    auto& ownTribe = context.ownTribe.get();
    ownTribe.setResourcesCount(foundResources + ownTribe.getResoucesCount());
    std::cout << "Worker " << _id << " found: " << foundResources << "; now have " << ownTribe.getResoucesCount() << "\n";
}