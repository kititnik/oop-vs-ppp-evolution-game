#ifndef __tribe__
#define __tribe__

#include "simulation_context.h"
#include "unit.h"
#include "container.h"
#include "battle_strategy.h"
#include "tribe_factory.h"

typedef struct SimulationContext SimulationContext;

// tribe.h - a tribe is like a collection of units with common resources(opaque pointer)
typedef struct Tribe Tribe;

Tribe* tribe_create(int unit_count, TribeFactory* factory, BattleStrategy* strategy);
void tribe_add(Tribe* tribe, Unit* unit);
// creates units using bound factory
void tribe_create_units(Tribe* tribe, int count, int id_offset);
void tribe_act_all(Tribe* tribe, SimulationContext* context);
Unit* get_random_alive_unit(Tribe* tribe);
Unit* get_weakest_alive_unit(Tribe* tribe);
BattleStrategy* tribe_get_strategy(Tribe* tribe);
void tribe_destroy(Tribe* tribe);

#endif // __tribe__
