#include <stdio.h>
#include "unit.h"
#include "worker.h"

void unit_act<Unit.warrior* unit>() {
    printf("Warrior %d is attacking\n", unit->id);
}
