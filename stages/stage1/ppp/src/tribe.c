#include <stdio.h>
#include <stdlib.h>
#include "tribe.h"

void tribe_create(Tribe* t, int unit_count) {
    t->unit_count = 0;
    ppVector_INIT(t->units);
}

void tribe_add(Tribe* t, Unit* unit) {
    ppVector_PUSH_BACK(t->units, unit);
    t->unit_count++;
}

void tribe_act_all(Tribe* tribe) {
    for (int i = 0; i < tribe->unit_count; ++i) {
        Unit* u;
        ppVector_GET_VAL_INDEX(u, tribe->units, i);
        unit_act<u>();
    }
}

void tribe_destroy(Tribe* tribe) {
    ppVector_destroy((ppVector*)&tribe->units);
}