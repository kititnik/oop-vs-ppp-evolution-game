#include "simulation.h"
#include "warrior.h"
#include "worker.h"
#include <stdlib.h>

Simulation simulation_create(int unit_count, int steps) {
    Simulation sim;
    tribe_create(&sim.tribe, unit_count);
    sim.steps = steps;
    sim.unit_count = unit_count;
    return sim;
}

void simulation_add_units(Simulation* sim) {
    for(int i = 0; i < sim->unit_count; ++i) {
        int rand_unit = rand() % 2;
        if(rand_unit) {
            Unit* u = create_spec(Unit.worker);
            u->id = i;
            tribe_add(&sim->tribe, u);
        }
        else {
            Unit* u = create_spec(Unit.warrior);
            u->id = i;
            tribe_add(&sim->tribe, u);
        }
    }
}

void simulation_run(Simulation* sim) {
    for (int step = 0; step < sim->steps; ++step) {
        printf("=== Step %d ===\n", step);
        tribe_act_all(&sim->tribe);
    }
}

void simulation_destroy(Simulation* sim) {
    tribe_destroy(&sim->tribe);
}