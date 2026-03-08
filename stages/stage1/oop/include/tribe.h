#ifndef __tribe__
#define __tribe__

#include <vector>
#include "unit.h"

class Tribe {
private:
    std::vector<std::unique_ptr<Unit>> _units;

public:
    Tribe();
    void actAll();
    void addUnit(std::unique_ptr<Unit> unit);
};

#endif // __tribe__