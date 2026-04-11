#ifndef __warrior__
#define __warrior__

#include "unit.h"
#include "worker.h"

typedef struct Warrior {
    int id;
    int health;
    int damage;
} Warrior;

Unit + <warrior: Warrior;>;

Unit* warrior_create(int id);
void warrior_attack<Unit.warrior* attacker, Unit.warrior* target>();
void warrior_attack<Unit.warrior* attacker, Unit.worker* target>();

#endif // __warrior__
