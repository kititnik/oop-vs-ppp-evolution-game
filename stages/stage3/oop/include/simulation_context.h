#ifndef __simulation_context__
#define __simulation_context__

#include <functional>

#include "tribe.h"

// simulation_context.h - for each tribe contains own and enemy tribe.
// Context changes every simulation move
struct SimulationContext {
    std::reference_wrapper<Tribe> ownTribe;
    std::reference_wrapper<Tribe> enemyTribe;
};

#endif // __simulation_context__