#ifndef __orc_factory__
#define __orc_factory__

#include "tribe_factory.h"

// orc_factory.h - factory for orc race.
// Creates only warriors with increased damage.
TribeFactory + <orc: void;>;

TribeFactory* orc_factory_create();
Unit* factory_create_unit<TribeFactory.orc* f>(int id);

#endif // __orc_factory__
