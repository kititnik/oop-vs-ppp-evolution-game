#ifndef __simulation__
#define __simulation__

#include "tribe.h"

class Simulation {
private:
    Tribe _tribe;
    int _steps;
    int _unitCount;

public:
    Simulation(int unitCount, int steps);
    void run();
    void createUnits();
};

#endif // __simulation__