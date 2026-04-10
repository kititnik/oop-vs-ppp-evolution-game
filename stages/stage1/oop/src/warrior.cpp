#include "warrior.h"
#include <iostream>

Warrior::Warrior(int id) : Unit(id) {}

void Warrior::act() {
    std::cout << "Warrior " << id << " is attacking\n";
}