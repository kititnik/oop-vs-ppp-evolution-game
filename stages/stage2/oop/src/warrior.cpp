#include <iostream>
#include <optional>
#include "warrior.h"
#include "simulation_context.h"
#include "tribe.h"

Warrior::Warrior(int id) : Unit(id) {
    damage = 35;
}

void Warrior::act(SimuationContext& context) {
    auto target = context.enemyTribe.get().getRandomAliveUnit();
    if(target == std::nullopt) {
        std::cout << "Warrior " << id << " didn't find enemy to attack\n";
        return;
    }
    target->get().takeDamage(damage);
    std::cout << "Warrior " << id << " is attacking " << target->get().getId() << ", target health " << target->get().getHealth() << "\n";
}