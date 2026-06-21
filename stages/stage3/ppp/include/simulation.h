#ifndef __simulation__
#define __simulation__

#include "tribe.h"

// simulation.h - represents the entire simulation state(opaque pointer)
typedef struct Simulation Simulation;

Simulation* simulation_create(int unit_count, int steps);
// generate and add units to tribes
void simulation_add_units(Simulation* sim);
void simulation_run(Simulation* sim);
void simulation_destroy(Simulation* sim);

#endif // __container__
