#include "simulation.h"
#include "tribe.h"
#include "warrior.h"
#include "worker.h"
#include "aggressive_strategy.h"
#include "random_strategy.h"
#include <stdlib.h>

struct Simulation {
    Tribe* tribe1;
    Tribe* tribe2;
    int steps;
    int unit_count;
};

Simulation* simulation_create(int unit_count, int steps) {
    Simulation* sim = malloc(sizeof(Simulation));
    Tribe* tribe1 = tribe_create(unit_count, random_strategy_create());
    Tribe* tribe2 = tribe_create(unit_count, aggressive_strategy_create());
    sim->tribe1 = tribe1;
    sim->tribe2 = tribe2;
    sim->steps = steps;
    sim->unit_count = unit_count;
    return sim;
}

void simulation_add_units(Simulation* sim) {
    for(int i = 0; i < sim->unit_count; ++i) {
        int rand_unit = rand() % 2;
        // The same type of unit is added to both tribes at once
        if(rand_unit == 1) {
            Unit* u1 = worker_create(i);
            Unit* u2 = worker_create(i+sim->unit_count);
            tribe_add(sim->tribe1, u1);
            tribe_add(sim->tribe2, u2);
        }
        else {
            Unit* u1 = warrior_create(i);
            Unit* u2 = warrior_create(i+sim->unit_count);
            tribe_add(sim->tribe1, u1);
            tribe_add(sim->tribe2, u2);
        }
    }
}

void simulation_run(Simulation* sim) {
    for (int step = 0; step < sim->steps; ++step) {
        printf("=== Step %d ===\n", step);

        SimulationContext contextTribe1;
        contextTribe1.own_tribe = sim->tribe1;
        contextTribe1.enemy_tribe = sim->tribe2;
        SimulationContext contextTribe2;
        contextTribe2.own_tribe = sim->tribe2;
        contextTribe2.enemy_tribe = sim->tribe1;

        tribe_act_all(sim->tribe1, &contextTribe1);
        tribe_act_all(sim->tribe2, &contextTribe2);
    }
}

void simulation_destroy(Simulation* sim) {
    tribe_destroy(sim->tribe1);
    tribe_destroy(sim->tribe2);
}