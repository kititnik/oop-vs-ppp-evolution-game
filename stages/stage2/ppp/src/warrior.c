#include <stdio.h>
#include "warrior.h"
#include "tribe.h"

Unit* warrior_create(int id) {
    Unit* u = create_spec(Unit.warrior);
    u->id = id;
    u->health = 100;
    u->@damage = 35;
    return u;
}

void unit_act<Unit.warrior* unit>(SimuationContext* context) {
    Unit* target = get_random_alive_unit(context->enemy_tribe);
    if(target == NULL) {
        printf("Warrior %d didn't find enemy to attack\n", unit->id);
        return;Н
    }
    warrior_attack<unit, target>();
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