#ifndef __simulation_context__
#define __simulation_context__

#include <functional>

#include "tribe.h"

struct SimuationContext {
    std::reference_wrapper<Tribe> ownTribe;
    std::reference_wrapper<Tribe> enemyTribe;
};

#endif // __simulation_context__