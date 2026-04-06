#ifndef __tribe__
#define __tribe__

#include <vector>
#include "unit.h"

struct SimuationContext;

class Tribe {
private:
    std::vector<std::unique_ptr<Unit>> _units;
    int _resourcesCount;

public:
    Tribe();
    void actAll(SimuationContext& context);
    void addUnit(std::unique_ptr<Unit> unit);
    std::optional<std::reference_wrapper<Unit>> getRandomAliveUnit();
    int getResoucesCount();
    void setResourcesCount(int resources);
};

#endif // __tribe__