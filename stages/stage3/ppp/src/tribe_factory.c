#include "tribe_factory.h"
#include <stdlib.h>

Unit* factory_create_unit<TribeFactory* f>(int id) {
    // overridden by specializations
    return NULL;
}