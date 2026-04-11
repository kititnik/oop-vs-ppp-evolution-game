#include "simulation.h"
#include "tribe.h"
#include "warrior.h"
#include "worker.h"
#include <stdlib.h>

struct Simulation {
    Tribe* tribe1;
    Tribe* tribe2;
    int steps;
    int unit_count;
};

Simulation* simulation_create(int unit_count, int steps) {
    Simulation* sim = malloc(sizeof(Simulation));
    Tribe* tribe1 = tribe_create(unit_count);
    Tribe* tribe2 = tribe_create(unit_count);
    sim->tribe1 = tribe1;
    sim->tribe2 = tribe2;
    sim->steps = steps;
    sim->unit_count = unit_count;
    return sim;
}

void simulation_add_units(Simulation* sim) {
    for(int i = 0; i < sim->unit_count; ++i) {
        int rand_unit = rand() % 2;
        if(rand_unit) {
            Unit* u = worker_create(i);
            tribe_add(sim->tribe1, u);
            tribe_add(sim->tribe2, u);
        }
        else {
            Unit* u = warrior_create(i);
            tribe_add(sim->tribe1, u);
            tribe_add(sim->tribe2, u);
        }
    }
}

void simulation_run(Simulation* sim) {
    for (int step = 0; step < sim->steps; ++step) {
        printf("=== Step %d ===\n", step);
        SimuationContext* contextTribe1;
        contextTribe1->own_tribe = sim->tribe1;
        contextTribe1->enemy_tribe = sim->tribe2;
        SimuationContext* contextTribe2;
        contextTribe2->own_tribe = sim->tribe2;
        contextTribe2->enemy_tribe = sim->tribe1;
        tribe_act_all(sim->tribe1, contextTribe1);
        tribe_act_all(sim->tribe2, contextTribe2);
    }
}

void simulation_destroy(Simulation* sim) {
    tribe_destroy(sim->tribe1);
    tribe_destroy(sim->tribe2);
}