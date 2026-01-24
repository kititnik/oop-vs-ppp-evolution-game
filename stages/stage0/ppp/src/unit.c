#include <stdio.h>

typedef struct Unit {
    int id;
} Unit;

void unit_act(Unit *unit) {
    printf("Unit %d acts\n", unit->id);
}