#include <iostream>

class Unit {
private:
    int _id;

public:
    Unit(int id) {
        _id = id;
    }

    void act() {
        std::cout << "Unit " << _id << " acts" << std::endl;
    }
};

