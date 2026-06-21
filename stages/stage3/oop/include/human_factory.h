#ifndef __human_factory__
#define __human_factory__

#include "tribe_factory.h"

// human_factory.h - factory for human race.
// Creates a random mix of warriors and workers.
class HumanFactory : public TribeFactory {
public:
    std::unique_ptr<Unit> createUnit(int id) override;
};

#endif // __human_factory__
