#include "unit.h"

Unit::Unit(int id) {
    _id = id;
    _health = 100;
}

bool Unit::isAlive() {
    return (_health > 0);
}

void Unit::takeDamage(int damage) {
    _health -= damage;
    if(_health < 0) _health = 0;
}

int Unit::getHealth() {
    return _health;
}

int Unit::getId() {
    return _id;
}
