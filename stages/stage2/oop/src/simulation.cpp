#include "simulation.h"
#include "warrior.h"
#include "worker.h"
#include <iostream>
#include <random>

Simulation::Simulation(int unitCount, int steps) : _tribe() {
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
            _tribe.addUnit(std::make_unique<Warrior>(i));
        }
        else {
            _tribe.addUnit(std::make_unique<Worker>(i));
        }
    }
}

void Simulation::run() {
    for (int step = 0; step < _steps; ++step) {
        std::cout << "=== Step " << step << " ===" << std::endl;
        _tribe.actAll();
    }
}