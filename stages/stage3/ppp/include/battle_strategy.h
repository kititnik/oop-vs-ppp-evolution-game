#ifndef __battle_strategy__
#define __battle_strategy__

#include "unit.h"

typedef struct SimulationContext SimulationContext;

// battle_strategy.h - generalization for unit behavior strategies.
// strategy_execute is a multimethod that dispatches over both
// strategy specialization and unit specialization at runtime.
typedef struct BattleStrategy {} <> BattleStrategy;

void strategy_execute<BattleStrategy* s, Unit* unit>(SimulationContext* context);

#endif // __battle_strategy__
