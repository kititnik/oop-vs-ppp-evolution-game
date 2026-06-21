#include <stdio.h>
#include "worker.h"
#include "battle_strategy.h"
#include "tribe.h"

Unit* worker_create(int id) {
    struct Unit.worker* u = create_spec(Unit.worker);
    u->id = id;
    u->health = 100;
    return (Unit*)u;
}


void unit_act<Unit.worker* unit>(SimulationContext* context) {
    BattleStrategy* strategy = tribe_get_strategy(context->own_tribe);
    strategy_execute<strategy, (Unit*)unit>(context);
}
