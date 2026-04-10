#include <stdio.h>
#include "unit.h"

Unit* warrior_create(int id) {
    Unit* u = create_spec(Unit.warrior);
    u->id = id;
    return u;
}

void unit_act<Unit.warrior* unit>() {
    printf("Warrior %d is attacking\n", unit->id);
}
