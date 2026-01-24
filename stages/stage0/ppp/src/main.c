#include "simulation.c"

int main(void) {
    const int UNIT_COUNT = 3;
    const int STEPS = 5;

    Simulation sim = simulation_create(UNIT_COUNT, STEPS);
    simulation_run(&sim);
    simulation_destroy(&sim);

    return 0;
}
