#include <stdio.h>
#include "unit_impl.h"

Unit* warrior_create(int id) {
    Unit* u = create_spec(Unit.warrior);
    u->_id = id;
    return u;
}

void unit_act<Unit.warrior* unit>() {
    printf("Warrior %d is attacking\n", unit->_id);
}
