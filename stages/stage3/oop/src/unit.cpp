#include "unit.h"

Unit::Unit(int id) {
    this->id = id;
    this->health = 100;
}

bool Unit::isAlive() {
    return (health > 0);
}

void Unit::takeDamage(int damage) {
    health -= damage;
    if(health < 0) health = 0;
}

int Unit::getHealth() {
    return health;
}

int Unit::getId() {
    return id;
}
