#ifndef __unit__
#define __unit__

#include "worker.h"
#include "warrior.h"

typedef struct Unit {
    int id;
    int health;
} <> Unit;

void unit_act<Unit *unit>();
bool is_alive(Unit* unit)
void take_damage(Unit* unit, int damage);
int get_health(Unit* unit);

Unit + <worker: Worker;>;
Unit + <warrior: Warrior;>;

#endif // __unit__
