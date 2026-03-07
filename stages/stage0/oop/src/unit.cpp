#include <iostream>
#include "unit.h"

Unit::Unit(int id) {
    _id = id;
}

void Unit::act() {
    std::cout << "Unit " << _id << " acts" << std::endl;
}