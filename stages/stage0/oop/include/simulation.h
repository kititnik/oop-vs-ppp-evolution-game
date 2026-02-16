#ifndef SIMULATION_H
#define SIMULATION_H

#include "tribe.h"

class Simulation {
private:
    Tribe _tribe;
    int _steps;

public:
    Simulation(int unitCount, int steps);
    void run();
};

#endif