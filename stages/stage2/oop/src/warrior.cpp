#include <iostream>
#include <optional>
#include "warrior.h"
#include "simulation_context.h"
#include "tribe.h"
#include "worker.h"

Warrior::Warrior(int id) : Unit(id) {
    damage = 35;
}

void Warrior::act(SimulationContext& context) {
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

// Warrior vs Warrior: damage is halved due to armor
// damage * 0.5 is an integer truncation
void Warrior::attackWarrior(Warrior& target) {
    target.takeDamage(damage * 0.5);
    std::cout << "Warrior " << id << " is attacking Warrior " << target.getId() << ", target health " << target.getHealth() << "\n";
}

// Warrior vs Worker: full damage
void Warrior::attackWorker(Worker& target) {
    target.takeDamage(damage);
    std::cout << "Warrior " << id << " is attacking Worker " << target.getId() << ", target health " << target.getHealth() << "\n";
}