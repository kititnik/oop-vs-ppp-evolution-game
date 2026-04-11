#include <stdio.h>

#include "unit.h"

void unit_act<Unit *unit>(SimuationContext* context) {
    // overridden by specializations
}

int is_alive(Unit* unit) {
    return (unit->health > 0);
}

void take_damage(Unit* unit, int damage) {
    unit->health -= damage;
    if(unit->health < 0) unit->health = 0;
}

int get_health(Unit* unit) {
    return unit->health;
}