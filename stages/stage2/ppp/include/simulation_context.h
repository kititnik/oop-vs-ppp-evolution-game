#ifndef __simulation_context__
#define __simulation_context__

typedef struct Tribe Tribe;

struct SimulationContext {
    Tribe* own_tribe;
    Tribe* enemy_tribe;
};

#endif // __simulation_context__