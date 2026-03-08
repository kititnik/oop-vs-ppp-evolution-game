#ifndef __simulation__
#define __simulation__

#include "tribe.h"

typedef struct Simulation {
    Tribe tribe;
    int steps;
    int unit_count;
} Simulation;

Simulation simulation_create(int unit_count, int steps);
void simulation_add_units(Simulation* sim);
void simulation_run(Simulation* sim);
void simulation_destroy(Simulation* sim);

#endif // __container__
