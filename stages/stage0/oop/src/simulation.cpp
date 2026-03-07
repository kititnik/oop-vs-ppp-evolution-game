#include "simulation.h"
#include <iostream>

Simulation::Simulation(int unitCount, int steps) : _tribe(unitCount) {
    _steps = steps;
}

void Simulation::run() {
    for (int step = 0; step < _steps; ++step) {
        std::cout << "=== Step " << step << " ===" << std::endl;
        _tribe.actAll();
    }
}