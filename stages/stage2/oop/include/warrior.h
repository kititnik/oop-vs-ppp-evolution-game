#ifndef __warrior__
#define __warrior__

#include "unit_attacker.h"
#include "unit.h"

// warrior.h - derived class from Unit with UnitAttacker abilities
class Warrior : public Unit, public UnitAttacker {
public:
    int damage;
public:
    Warrior(int id);
    void act(SimulationContext& context) override;
    void acceptAttack(UnitAttacker& attacker) override;
    void attackWarrior(Warrior& target) override;
    void attackWorker(Worker& targer) override;
};

#endif // __warrior__