#ifndef __warrior__
#define __warrior__

#include "unit.h"

class Warrior : public Unit {
public:
    int damage;
public:
    Warrior(int id);
    void act(SimuationContext& context) override;
};

#endif // __warrior__