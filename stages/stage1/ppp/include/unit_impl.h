#ifndef __unit_impl__
#define __unit_impl__

#include "unit.h"
#include "warrior_impl.h"
#include "worker_impl.h"

typedef struct Unit {
    int _id;
} <> Unit;

Unit + <worker: Worker;>;
Unit + <warrior: Warrior;>;

#endif // __unit_impl__