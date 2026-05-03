#include <stdio.h>
#include "worker.h"

Unit* worker_create(int id) {
    struct Unit.worker* u = create_spec(Unit.worker);
    u->id = id;
    u->health = 100;
    return (Unit*)u;
}


void unit_act<Unit.worker* unit>(SimulationContext* context) {
    printf("Worker %d is working\n", unit->id);
}
