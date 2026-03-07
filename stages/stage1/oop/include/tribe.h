#ifndef __tribe__
#define __tribe__

#include <vector>
#include "unit.h"

class Tribe {
private:
    std::vector<Unit> _units;

public:
    Tribe(int unitCount);
    void actAll();
};

#endif // __tribe__