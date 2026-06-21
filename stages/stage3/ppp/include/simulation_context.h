#ifndef __simulation_context__
#define __simulation_context__

typedef struct Tribe Tribe;

// simulation_context.h - for each tribe contains own and enemy tribe.
// Context changes every simulation move
struct SimulationContext {
    Tribe* own_tribe;
    Tribe* enemy_tribe;
};

#endif // __simulation_context__