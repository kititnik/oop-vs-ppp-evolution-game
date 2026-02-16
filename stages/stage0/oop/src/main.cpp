#include "simulation.h"

int main() {
  const int UNIT_COUNT = 3;
  const int STEPS = 5;

  Simulation simulation(UNIT_COUNT, STEPS);
  simulation.run();

  return 0;
}