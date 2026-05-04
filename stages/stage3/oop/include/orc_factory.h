#ifndef __orc_factory__
#define __orc_factory__

#include "tribe_factory.h"

// orc_factory.h - factory for orc race.
// Creates only warriors with increased damage.
class OrcFactory : public TribeFactory {
public:
    std::unique_ptr<Unit> createUnit(int id) override;
};

#endif // __orc_factory__
