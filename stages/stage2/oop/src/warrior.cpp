#include <iostream>
#include <optional>
#include "warrior.h"
#include "simulation_context.h"
#include "tribe.h"
#include "worker.h"

Warrior::Warrior(int id) : Unit(id) {
    damage = 35;
}

void Warrior::act(SimuationContext& context) {
    auto target = context.enemyTribe.get().getRandomAliveUnit();
    if(target == std::nullopt) {
        std::cout << "Warrior " << id << " didn't find enemy to attack\n";
        return;
    }
    target->get().acceptAttack(*this);
}

void Warrior::acceptAttack(UnitAttacker& attacker) {
    attacker.attackWarrior(*this);
}

void Warrior::attackWarrior(Warrior& target) {
    target.takeDamage(damage * 0.5);
    std::cout << "Warrior " << id << " is attacking Warrior " << target.getId() << ", target health " << target.getHealth() << "\n";
}

void Warrior::attackWorker(Worker& target) {
    target.takeDamage(damage);
    std::cout << "Warrior " << id << " is attacking Worker " << target.getId() << ", target health " << target.getHealth() << "\n";
}