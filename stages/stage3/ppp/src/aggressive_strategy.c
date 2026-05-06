#include <stdio.h>
#include "aggressive_strategy.h"
#include "tribe.h"
#include "warrior.h"

BattleStrategy* aggressive_strategy_create() {
    return create_spec(BattleStrategy.aggressive);
}

void strategy_execute<BattleStrategy.aggressive* s, Unit.warrior* unit>(SimulationContext* context) {
    Unit* target = get_weakest_alive_unit(context->enemy_tribe);
    if(target == NULL) {
        printf("Warrior %d didn't find enemy to attack\n", unit->id);
        return;
    }
    warrior_attack<(Unit*)unit, target>();
}

void strategy_execute<BattleStrategy.aggressive* s, Unit.worker* unit>(SimulationContext* context) {
    printf("Worker %d aggresively do nothing\n", unit->id);
}
