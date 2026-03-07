#include <stdio.h>
#include "unit.h"

void unit_act(Unit *unit) {
    printf("Unit %d acts\n", unit->id);
}
