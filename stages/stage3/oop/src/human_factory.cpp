#include <cstdlib>
#include "human_factory.h"
#include "warrior.h"
#include "worker.h"

std::unique_ptr<Unit> HumanFactory::createUnit(int id) {
    if (rand() % 2) {
        return std::make_unique<Warrior>(id, 35);
    } else {
        return std::make_unique<Worker>(id);
    }
}
