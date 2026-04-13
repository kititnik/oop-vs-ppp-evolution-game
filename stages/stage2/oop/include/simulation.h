#ifndef __simulation__
#define __simulation__

#include "tribe.h"

// simulation.h - represents the entire simulation state
class Simulation {
private:
    Tribe _tribe1;
    Tribe _tribe2;
    int _steps;
    int _unitCount;

public:
    Simulation(int unitCount, int steps);
    // start simulation
    void run();
    // generate and add units to tribe
    void createUnits();
};

#endif // __simulation__