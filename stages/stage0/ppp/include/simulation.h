#ifndef SIMULATION_H
#define SIMULATION_H

#include "tribe.h"

typedef struct Simulation {
    Tribe tribe;
    int steps;
} Simulation;

Simulation simulation_create(int unit_count, int steps);
void simulation_run(Simulation* sim);
void simulation_destroy(Simulation* sim);

#endif
