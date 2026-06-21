#include <stdlib.h>
#include "human_factory.h"
#include "warrior.h"
#include "worker.h"

TribeFactory* human_factory_create() {
    return create_spec(TribeFactory.human);
}

Unit* factory_create_unit<TribeFactory.human* f>(int id) {
    if (rand() % 2) {
        return warrior_create(id, 35);
    } else {
        return worker_create(id);
    }
}
