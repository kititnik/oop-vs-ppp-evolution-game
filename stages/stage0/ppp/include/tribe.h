#ifndef TRIBE_H
#define TRIBE_H

#include "unit.h"
#include "container.h"

typedef struct Tribe {
    struct ppVector.unit units;
    int unit_count;
} Tribe;

void tribe_create(Tribe* t, int unit_count);
void tribe_act_all(Tribe* tribe);
void tribe_destroy(Tribe* tribe);

#endif
