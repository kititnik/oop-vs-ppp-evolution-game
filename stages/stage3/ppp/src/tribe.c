#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "tribe.h"

struct Tribe {
    struct ppVector.unit units;
    int unit_count;
    BattleStrategy* strategy;
    TribeFactory* factory;
};

Tribe* tribe_create(int unit_count, TribeFactory* factory, BattleStrategy* strategy) {
    Tribe* t = malloc(sizeof(Tribe));
    t->unit_count = 0;
    t->factory = factory;
    t->strategy = strategy;
    ppVector_INIT(t->units);
    return t;
}

void tribe_add(Tribe* t, Unit* unit) {
    ppVector_PUSH_BACK(t->units, unit);
    t->unit_count++;
}

void tribe_create_units(Tribe* tribe, int count, int id_offset) {
    for(int i = 0; i < count; ++i) {
        Unit* u = factory_create_unit<tribe->factory>(id_offset + i);
        tribe_add(tribe, u);
    }
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
    // Two passes: first we count the live ones, then we go to the desired one.
    // Does not require an additional buffer.
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

Unit* get_weakest_alive_unit(Tribe* tribe) {
    Unit* weakest = NULL;
    int min_health = INT_MAX;
    for(int i = 0; i < tribe->unit_count; ++i) {
        Unit* u;
        ppVector_GET_VAL_INDEX(u, tribe->units, i);
        if(is_alive(u) && get_health(u) < min_health) {
            min_health = get_health(u);
            weakest = u;
        }
    }
    return weakest;
}

BattleStrategy* tribe_get_strategy(Tribe* tribe) {
    return tribe->strategy;
}

void tribe_destroy(Tribe* tribe) {
    ppVector_destroy((ppVector*)&tribe->units);
}