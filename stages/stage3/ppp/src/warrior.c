#include <stdio.h>
#include "warrior.h"
#include "tribe.h"
#include "battle_strategy.h"

Unit* warrior_create(int id, int damage) {
    struct Unit.warrior* u = create_spec(Unit.warrior);
    u->id = id;
    u->health = 100;
    u->@damage = damage;
    return (Unit*)u;
}

void warrior_attack<Unit* attacker, Unit* target>() {} //= 0;

void unit_act<Unit.warrior* unit>(SimulationContext* context) {
    BattleStrategy* strategy = tribe_get_strategy(context->own_tribe);
    strategy_execute<strategy, (Unit*)unit>(context);
}

void warrior_attack<Unit.warrior* attacker, Unit.warrior* target>()
{
    take_damage((Unit*)target, attacker->@damage * 0.5);
    printf("Warrior %d is attacking warrior %d, target health %d\n", attacker->id, target->id, target->health);
}

void warrior_attack<Unit.warrior* attacker, Unit.worker* target>() {
    take_damage((Unit*)target, attacker->@damage);
    printf("Warrior %d is attacking worker %d, target health %d\n", attacker->id, target->id, target->health);
}