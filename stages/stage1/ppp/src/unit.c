#include <stdio.h>
#include "unit_impl.h"

void unit_act<Unit *unit>() {
    // overridden by specializations
}

int get_id(Unit* unit) {
    return unit->_id;
}