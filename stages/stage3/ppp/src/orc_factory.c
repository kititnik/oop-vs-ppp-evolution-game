#include "orc_factory.h"
#include "warrior.h"

TribeFactory* orc_factory_create() {
    return create_spec(TribeFactory.orc);
}

Unit* factory_create_unit<TribeFactory.orc* f>(int id) {
    return warrior_create(id, 50);
}
