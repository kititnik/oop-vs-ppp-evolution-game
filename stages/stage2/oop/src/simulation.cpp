#include "simulation.h"
#include "simulation_context.h"
#include "warrior.h"
#include "worker.h"
#include <iostream>
#include <random>

Simulation::Simulation(int unitCount, int steps) : _tribe1(), _tribe2() {
    _unitCount = unitCount;
    _steps = steps;
}

void Simulation::createUnits() {
    std::random_device dev;
    std::mt19937 rng(dev());
    for(int i = 0; i < _unitCount; ++i)
    {
        std::uniform_int_distribution<std::mt19937::result_type> dist6(0,1);
        if(dist6(rng)) {
            _tribe1.addUnit(std::make_unique<Warrior>(i));
            _tribe2.addUnit(std::make_unique<Warrior>(i+_unitCount));
        }
        else {
            _tribe1.addUnit(std::make_unique<Worker>(i));
            _tribe2.addUnit(std::make_unique<Worker>(i+_unitCount));
        }
    }
}

void Simulation::run() {
    for (int step = 0; step < _steps; ++step) {
        std::cout << "=== Step " << step << " ===" << std::endl;
        SimuationContext contextTribe1 = { _tribe1, _tribe2 };
        SimuationContext contextTribe2 = { _tribe2, _tribe1 };
        _tribe1.actAll(contextTribe1);
        _tribe2.actAll(contextTribe2);
    }
}