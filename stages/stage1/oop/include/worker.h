#ifndef __worker__
#define __worker__

#include "unit.h"

class Worker : public Unit {
public:
    Worker(int id);
    void act() override;
};

#endif // __worker__