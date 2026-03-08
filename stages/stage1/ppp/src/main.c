#include "simulation.h"
#include <time.h>
#include <stdlib.h>

int main(void) {
    const int UNIT_COUNT = 3;
    const int STEPS = 5;
    srand(time(NULL));
    Simulation sim = simulation_create(UNIT_COUNT, STEPS);
    simulation_add_units(&sim);
    simulation_run(&sim);
    simulation_destroy(&sim);

    return 0;
}
