#ifndef __random_strategy__
#define __random_strategy__

#include "battle_strategy.h"

// random_strategy.h - default strategy.
// Warriors attack random alive enemy, workers gather resources.
class RandomStrategy : public BattleStrategy {
public:
    void actWarrior(Warrior& unit, SimulationContext& context) override;
    void actWorker(Worker& unit, SimulationContext& context) override;
};

#endif // __random_strategy__
