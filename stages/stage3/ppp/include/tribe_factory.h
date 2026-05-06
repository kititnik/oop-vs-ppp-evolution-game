#ifndef __tribe_factory__
#define __tribe_factory__

#include "unit.h"

// tribe_factory.h - generalization for unit factories.
// Each specialization decides which units to create.
typedef struct TribeFactory {} <> TribeFactory;

Unit* factory_create_unit<TribeFactory* f>(int id);

#endif // __tribe_factory__
