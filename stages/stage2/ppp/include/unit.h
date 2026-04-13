#ifndef __unit__
#define __unit__

typedef struct SimulationContext SimulationContext;

// unit.h - generalization representing any unit in the simulation
typedef struct Unit {
    int id;
    int health;
} <> Unit;

// This method is called when it is the unit's turn in simulation step.
void unit_act<Unit *unit>(SimulationContext* context);
int is_alive(Unit* unit);
void take_damage(Unit* unit, int damage);
int get_health(Unit* unit);

#endif // __unit__
