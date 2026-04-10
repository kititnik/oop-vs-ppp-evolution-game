#ifndef __worker__
#define __worker__

typedef struct Unit Unit;

typedef struct Worker {
    int id;
    int health;
} Worker;

Unit* worker_create(int id);

#endif // __worker__
