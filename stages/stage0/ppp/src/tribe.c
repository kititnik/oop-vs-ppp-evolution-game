#include <stdio.h>
#include <stdlib.h>
#include "unit.c"
#include "container.h"

typedef struct Tribe {
    struct ppVector.unit units;
    int unit_count;
} Tribe;

Tribe tribe_create(int unit_count) {
    Tribe tribe;
    tribe.unit_count = unit_count;
    tribe.units.foundation_size = sizeof(tribe.units.@);
    tribe.units.foundation_addr = &(tribe.units.@);
    tribe.units.size = 0;
    tribe.units.capacity = 0;
    tribe.units.vec_memory = NULL;

    for (int i = 0; i < unit_count; ++i) {
        Unit u;
        u.id = i;
        ppVector_PUSH_BACK(tribe.units, u)
    }

    return tribe;
}

void tribe_act_all(Tribe* tribe) {
    for (int i = 0; i < tribe->unit_count; ++i) {
        Unit u;
        ppVector_GET_VAL_INDEX(u, tribe->units, i);
        unit_act(&u);
    }
}

void tribe_destroy(Tribe* tribe) {
    ppVector_destroy((ppVector*)&tribe->units);
}