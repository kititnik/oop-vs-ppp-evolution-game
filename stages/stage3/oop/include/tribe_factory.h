#ifndef __tribe_factory__
#define __tribe_factory__

#include <memory>

class Unit;

// tribe_factory.h - interface for creating tribe units.
// Different races have their own factories, that decide what units to create.
class TribeFactory {
public:
    virtual std::unique_ptr<Unit> createUnit(int id) = 0;
    virtual ~TribeFactory() = default;
};

#endif // __tribe_factory__
