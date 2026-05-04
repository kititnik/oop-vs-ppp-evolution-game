#include "simulation.h"
#include "simulation_context.h"
#include "human_factory.h"
#include "orc_factory.h"
#include "aggressive_strategy.h"
#include "random_strategy.h"
#include <iostream>

Simulation::Simulation(int unitCount, int steps) 
    : _tribe1(std::make_unique<HumanFactory>(), std::make_unique<RandomStrategy>()), 
      _tribe2(std::make_unique<OrcFactory>(), std::make_unique<AggressiveStrategy>()) {
    _unitCount = unitCount;
    _steps = steps;
}

void Simulation::createUnits() {
    _tribe1.createUnits(_unitCount, 0);
    _tribe2.createUnits(_unitCount, _unitCount);
}

void Simulation::run() {
    for (int step = 0; step < _steps; ++step) {
        std::cout << "=== Step " << step << " ===" << std::endl;
        // Create special context for each tribe
        SimulationContext contextTribe1 = { _tribe1, _tribe2 };
        SimulationContext contextTribe2 = { _tribe2, _tribe1 };
        _tribe1.actAll(contextTribe1);
        _tribe2.actAll(contextTribe2);
    }
}