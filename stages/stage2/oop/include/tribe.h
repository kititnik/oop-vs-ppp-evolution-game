#ifndef __tribe__
#define __tribe__

#include <vector>
#include "unit.h"

struct SimuationContext;

class Tribe {
private:
    std::vector<std::unique_ptr<Unit>> _units;

public:
    Tribe();
    void actAll(SimuationContext& context);
    void addUnit(std::unique_ptr<Unit> unit);
    std::optional<std::reference_wrapper<Unit>> getRandomAliveUnit();
};

#endif // __tribe__