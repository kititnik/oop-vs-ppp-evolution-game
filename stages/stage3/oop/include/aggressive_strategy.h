#ifndef __aggressive_strategy__
#define __aggressive_strategy__

#include "battle_strategy.h"

// aggressive_strategy.h - aggressive strategy.
// Warriors attack the weakest alive enemy, workers do nothing.
class AggressiveStrategy : public BattleStrategy {
public:
    void actWarrior(Warrior& unit, SimulationContext& context) override;
    void actWorker(Worker& unit, SimulationContext& context) override;
};

#endif // __aggressive_strategy__
