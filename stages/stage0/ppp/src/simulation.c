#include "tribe.c"

typedef struct Simulation {
    Tribe tribe;
    int steps;
} Simulation;

Simulation simulation_create(int unit_count, int steps) {
    Simulation sim;
    tribe_create(&sim.tribe, unit_count);
    sim.steps = steps;
    return sim;
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