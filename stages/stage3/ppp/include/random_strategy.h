#ifndef __random_strategy__
#define __random_strategy__

#include "battle_strategy.h"
#include "warrior.h"
#include "worker.h"

// random_strategy.h - default strategy.
// Warriors attack random alive enemy, workers gather resources.
BattleStrategy + <random: void;>;

BattleStrategy* random_strategy_create();
void strategy_execute<BattleStrategy.random* s, Unit.warrior* unit>(SimulationContext* context);
void strategy_execute<BattleStrategy.random* s, Unit.worker* unit>(SimulationContext* context);

#endif // __random_strategy__
