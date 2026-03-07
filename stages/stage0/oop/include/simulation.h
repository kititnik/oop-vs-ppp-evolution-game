#ifndef __simulation__
#define __simulation__

#include "tribe.h"

class Simulation {
private:
    Tribe _tribe;
    int _steps;

public:
    Simulation(int unitCount, int steps);
    void run();
};

#endif // __simulation__