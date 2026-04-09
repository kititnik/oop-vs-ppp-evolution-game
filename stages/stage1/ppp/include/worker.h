#ifndef __worker__
#define __worker__

typedef struct Worker Worker;
typedef struct Unit Unit;

Unit* worker_create(int id);

#endif // __worker__
