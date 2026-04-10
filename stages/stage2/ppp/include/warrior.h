#ifndef __warrior__
#define __warrior__

typedef struct Unit Unit;

typedef struct Warrior {
    int id;
    int health;
} Warrior;

Unit* warrior_create(int id);

#endif // __warrior__
