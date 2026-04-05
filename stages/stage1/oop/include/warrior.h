#ifndef __warrior__
#define __warrior__

#include "unit.h"

class Warrior : public Unit {
public:
    Warrior(int id);
    void act() override;
};

#endif // __warrior__