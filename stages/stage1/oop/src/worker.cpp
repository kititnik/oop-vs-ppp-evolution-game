#include "worker.h"
#include <iostream>

Worker::Worker(int id) : Unit(id) {}

void Worker::act() {
    std::cout << "Worker " << _id << " is working\n";
}