#ifndef __warrior__
#define __warrior__

#include "unit.h"
#include "worker.h"

// warrior.h - specialization of Unit
typedef struct Warrior {
    int id;
    int health;
    int damage;
} Warrior;

Unit + <warrior: Warrior;>;

Unit* warrior_create(int id);
void warrior_attack<Unit* attacker, Unit* target>();
// multimethod to attack warrior. Damage is halved due to armor
// damage * 0.5 is an integer truncation
void warrior_attack<Unit.warrior* attacker, Unit.warrior* target>();
// multimethod to attack worker. Full damage
void warrior_attack<Unit.warrior* attacker, Unit.worker* target>();

#endif // __warrior__
