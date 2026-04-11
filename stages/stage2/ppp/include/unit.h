#ifndef __unit__
#define __unit__

typedef struct SimuationContext SimuationContext;

typedef struct Unit {
    int id;
    int health;
} <> Unit;

void unit_act<Unit *unit>(SimuationContext* context);
int is_alive(Unit* unit);
void take_damage(Unit* unit, int damage);
int get_health(Unit* unit);

#endif // __unit__
