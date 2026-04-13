#include <stdio.h>
#include <stdlib.h>

#include "tribe.h"

struct Tribe {
    struct ppVector.unit units;
    int unit_count;
};

Tribe* tribe_create(int unit_count) {
    Tribe* t = malloc(sizeof(Tribe));
    t->unit_count = 0;
    ppVector_INIT(t->units);
    return t;
}

void tribe_add(Tribe* t, Unit* unit) {
    ppVector_PUSH_BACK(t->units, unit);
    t->unit_count++;
}

void tribe_act_all(Tribe* tribe, SimulationContext* context) {
    for (int i = 0; i < tribe->unit_count; ++i) {
        Unit* u;
        ppVector_GET_VAL_INDEX(u, tribe->units, i);
        if(!is_alive(u)) continue;
        unit_act<u>(context);
    }
}

Unit* get_random_alive_unit(Tribe* tribe) {
    int alive_count = 0;
    for(int i = 0; i < tribe->unit_count; ++i) {
        Unit* u;
        ppVector_GET_VAL_INDEX(u, tribe->units, i);
        if(is_alive(u)) {
            alive_count++;
        }
    }
    if(alive_count == 0) return NULL;

    int target = rand() % alive_count;
    for(int i = 0; i < tribe->unit_count; ++i) {
        Unit* u;
        ppVector_GET_VAL_INDEX(u, tribe->units, i);
        if(!is_alive(u)) {
            continue;
        }
        if(target == 0) {
            return u;
        }
        target--;
    }
    return NULL;
}

void tribe_destroy(Tribe* tribe) {
    ppVector_destroy((ppVector*)&tribe->units);
}