#ifndef __aggressive_strategy__
#define __aggressive_strategy__

#include "battle_strategy.h"
#include "warrior.h"
#include "worker.h"

// aggressive_strategy.h - aggressive strategy.
// Warriors attack the weakest alive enemy, workers do nothing.
BattleStrategy + <aggressive: void;>;

BattleStrategy* aggressive_strategy_create();
void strategy_execute<BattleStrategy.aggressive* s, Unit.warrior* unit>(SimulationContext* context);
void strategy_execute<BattleStrategy.aggressive* s, Unit.worker* unit>(SimulationContext* context);

#endif // __aggressive_strategy__
