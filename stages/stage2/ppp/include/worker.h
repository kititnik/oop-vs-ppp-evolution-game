#ifndef __worker__
#define __worker__

#include "unit.h"

typedef struct Worker {
    int id;
    int health;
} Worker;

Unit + <worker: Worker;>;

Unit* worker_create(int id);

#endif // __worker__
