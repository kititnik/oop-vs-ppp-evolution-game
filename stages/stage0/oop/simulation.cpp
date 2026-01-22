#include "tribe.cpp"

class Simulation {
private:
    Tribe _tribe;
    int _steps;

public:
    Simulation(int unitCount, int steps) : _tribe(unitCount) {
        _steps = steps;
    }

    void run() {
        for (int step = 0; step < _steps; ++step) {
            std::cout << "=== Step " << step << " ===" << std::endl;
            _tribe.actAll();
        }
    }
};
