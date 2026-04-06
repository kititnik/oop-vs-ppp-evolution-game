#include <iostream>
#include <optional>
#include "warrior.h"
#include "simulation_context.h"
#include "tribe.h"

Warrior::Warrior(int id) : Unit(id) {
    _damage = 35;
}

void Warrior::act(SimuationContext& context) {
    auto target = context.enemyTribe.get().getRandomAliveUnit();
    if(target == std::nullopt) {
        std::cout << "Warrior " << _id << " didn't find enemy to attack\n";
        return;
    }
    target->get().takeDamage(_damage);
    std::cout << "Warrior " << _id << " is attacking " << target->get().getId() << ", target health " << target->get().getHealth() << "\n";
}