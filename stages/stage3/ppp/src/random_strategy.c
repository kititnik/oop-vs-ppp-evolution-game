#include <stdio.h>
#include "random_strategy.h"
#include "tribe.h"
#include "warrior.h"

BattleStrategy* random_strategy_create() {
    return create_spec(BattleStrategy.random);
}

void strategy_execute<BattleStrategy.random* s, Unit.warrior* unit>(SimulationContext* context) {
    Unit* target = get_random_alive_unit(context->enemy_tribe);
    if(target == NULL) {
        printf("Warrior %d didn't find enemy to attack\n", unit->id);
        return;
    }
    warrior_attack<(Unit*)unit, target>();
}

void strategy_execute<BattleStrategy.random* s, Unit.worker* unit>(SimulationContext* context) {
    printf("Worker %d is working\n", unit->id);
}
