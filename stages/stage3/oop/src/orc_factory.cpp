#include "orc_factory.h"
#include "warrior.h"

std::unique_ptr<Unit> OrcFactory::createUnit(int id) {
    return std::make_unique<Warrior>(id, 50);
}
