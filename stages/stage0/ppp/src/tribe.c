#include <stdio.h>
#include <stdlib.h>
#include "unit.c"

typedef struct Tribe {
    Unit* units;
    int unit_count;
} Tribe;

Tribe tribe_create(int unit_count) {
    Tribe tribe;
    tribe.unit_count = unit_count;
    tribe.units = (Unit*)malloc(sizeof(Unit) * unit_count);

    for (int i = 0; i < unit_count; ++i) {
        tribe.units[i].id = i;
    }

    return tribe;
}

void tribe_act_all(Tribe* tribe) {
    for (int i = 0; i < tribe->unit_count; ++i) {
        unit_act(&tribe->units[i]);
    }
}

void tribe_destroy(Tribe* tribe) {
    free(tribe->units);
}



