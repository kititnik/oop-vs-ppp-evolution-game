#ifndef __unit__
#define __unit__

#include "worker.h"
#include "warrior.h"

typedef struct Unit Unit;

void unit_act<Unit *unit>();
int get_id(Unit* unit);

#endif // __unit__
