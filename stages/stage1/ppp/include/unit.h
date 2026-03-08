#ifndef __unit__
#define __unit__

#include "worker.h"
#include "warrior.h"

typedef struct Unit {
    int id;
} <> Unit;

void unit_act<Unit *unit>();

Unit + <worker: Worker;>;
Unit + <warrior: Warrior;>;

#endif // __unit__
