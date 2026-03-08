#include <stdio.h>
#include "unit.h"
#include "worker.h"

void unit_act<Unit.worker* unit>() {
    printf("Worker %d is working\n", unit->id);
}
