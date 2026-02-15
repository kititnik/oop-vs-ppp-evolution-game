#include <stdio.h>
#include <stdlib.h>
#include "unit.c"
#include "container.h"

typedef struct Tribe {
    struct ppVector.unit units;
    int unit_count;
} Tribe;

void tribe_create(Tribe* t, int unit_count) {
    t->unit_count = unit_count;
    ppVector_INIT(t->units)

    for (int i = 0; i < unit_count; ++i) {
        Unit u;
        u.id = i;
        ppVector_PUSH_BACK(t->units, u)
    }
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