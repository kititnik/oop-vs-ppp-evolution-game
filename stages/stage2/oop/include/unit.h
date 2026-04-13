#ifndef __unit__
#define __unit__

#include "unit_attacker.h"

struct SimulationContext;

// unit.h - base class representing any unit in the simulation 
class Unit {
public:
    int id;
    int health;

public:
    Unit(int id);
    // This method is called when it is the unit's turn in simulation step.
    virtual void act(SimulationContext& context) = 0;
    bool isAlive();
    // This method is called when a unit is under attack.
    // You should call attacker.attack{your unit type}(e.g. attacker.attackWorker(target)) 
    // here to get an attack
    virtual void acceptAttack(UnitAttacker& attacker) = 0;
    void takeDamage(int damage);
    int getHealth();
    int getId();
    virtual ~Unit() = default;
};

#endif // __unit__