#ifndef __worker__
#define __worker__

#include "unit.h"

// worker.h - derived class from Unit
class Worker : public Unit {
public:
    Worker(int id);
    void act(SimulationContext& context) override;
    void acceptAttack(UnitAttacker& attacker) override;
};

#endif // __worker__