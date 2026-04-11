#ifndef __tribe__
#define __tribe__

#include "simulation_context.h"
#include "unit.h"
#include "container.h"

typedef struct SimuationContext SimuationContext;
typedef struct Tribe Tribe;

Tribe* tribe_create(int unit_count);
void tribe_add(Tribe* tribe, Unit* unit);
void tribe_act_all(Tribe* tribe, SimuationContext* context);
Unit* get_random_alive_unit(Tribe* tribe);
void tribe_destroy(Tribe* tribe);

#endif // __tribe__
