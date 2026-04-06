#include "worker.h"
#include <iostream>

Worker::Worker(int id) : Unit(id) {}

void Worker::act(SimuationContext& context) {
    std::cout << "Worker " << _id << " is working\n";
}