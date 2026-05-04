#include <iostream>
#include "warrior.h"
#include "simulation_context.h"
#include "tribe.h"
#include "worker.h"

Warrior::Warrior(int id, int damage) : Unit(id) {
    this->damage = damage;
}

void Warrior::act(SimulationContext& context) {
    context.ownTribe.get().getStrategy().actWarrior(*this, context);
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