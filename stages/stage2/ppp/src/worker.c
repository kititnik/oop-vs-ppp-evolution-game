#include <stdio.h>
#include "unit.h"

Unit* worker_create(int id) {
    Unit* u = create_spec(Unit.worker);
    u->id = id;
    return u;
}


void unit_act<Unit.worker* unit>() {
    printf("Worker %d is working\n", unit->id);
}
