#ifndef __human_factory__
#define __human_factory__

#include "tribe_factory.h"

// human_factory.h - factory for human race.
// Creates a random mix of warriors and workers.
TribeFactory + <human: void;>;

TribeFactory* human_factory_create();
Unit* factory_create_unit<TribeFactory.human* f>(int id);

#endif // __human_factory__
