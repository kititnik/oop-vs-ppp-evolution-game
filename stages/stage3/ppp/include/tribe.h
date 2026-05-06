#ifndef __tribe__
#define __tribe__

#include "simulation_context.h"
#include "unit.h"
#include "container.h"
#include "battle_strategy.h"

typedef struct SimulationContext SimulationContext;

// tribe.h - a tribe is like a collection of units with common resources(opaque pointer)
typedef struct Tribe Tribe;

Tribe* tribe_create(int unit_count, BattleStrategy* strategy);
void tribe_add(Tribe* tribe, Unit* unit);
void tribe_act_all(Tribe* tribe, SimulationContext* context);
Unit* get_random_alive_unit(Tribe* tribe);
Unit* get_weakest_alive_unit(Tribe* tribe);
BattleStrategy* tribe_get_strategy(Tribe* tribe);
void tribe_destroy(Tribe* tribe);

#endif // __tribe__
