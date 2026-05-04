#ifndef __tribe__
#define __tribe__

#include <vector>
#include "unit.h"
#include "battle_strategy.h"

struct SimulationContext;

// tribe.h - a tribe is like a collection of units with common resources
class Tribe {
private:
    std::vector<std::unique_ptr<Unit>> _units;
    int _resourcesCount;
    std::unique_ptr<BattleStrategy> _strategy;

public:
    Tribe(std::unique_ptr<BattleStrategy> strategy);
    void actAll(SimulationContext& context);
    void addUnit(std::unique_ptr<Unit> unit);
    std::optional<std::reference_wrapper<Unit>> getRandomAliveUnit();
    std::optional<std::reference_wrapper<Unit>> getWeakestAliveUnit();
    int getResourcesCount();
    void setResourcesCount(int resources);
    BattleStrategy& getStrategy();
};

#endif // __tribe__