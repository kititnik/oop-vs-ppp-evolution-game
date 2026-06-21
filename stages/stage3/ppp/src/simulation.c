#include "simulation.h"
#include "tribe.h"
#include "warrior.h"
#include "worker.h"
#include "aggressive_strategy.h"
#include "random_strategy.h"
#include "human_factory.h"
#include "orc_factory.h"
#include <stdlib.h>

struct Simulation {
    Tribe* tribe1;
    Tribe* tribe2;
    int steps;
    int unit_count;
};

Simulation* simulation_create(int unit_count, int steps) {
    Simulation* sim = malloc(sizeof(Simulation));
    Tribe* tribe1 = tribe_create(unit_count, human_factory_create(), random_strategy_create());
    Tribe* tribe2 = tribe_create(unit_count, orc_factory_create(), aggressive_strategy_create());
    sim->tribe1 = tribe1;
    sim->tribe2 = tribe2;
    sim->steps = steps;
    sim->unit_count = unit_count;
    return sim;
}

void simulation_add_units(Simulation* sim) {
    // Each tribe uses its own factory to populate units
    tribe_create_units(sim->tribe1, sim->unit_count, 0);
    tribe_create_units(sim->tribe2, sim->unit_count, sim->unit_count);
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