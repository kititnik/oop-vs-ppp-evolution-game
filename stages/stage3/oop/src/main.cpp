#include "simulation.h"

int main() {
  srand(time(nullptr));
  const int UNIT_COUNT = 3;
  const int STEPS = 5;

  Simulation simulation(UNIT_COUNT, STEPS);
  simulation.createUnits();
  simulation.run();

  return 0;
}