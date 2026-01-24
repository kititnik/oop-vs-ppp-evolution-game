#include <vector>
#include "unit.cpp"

class Tribe {
private:
    std::vector<Unit> _units;

public:
    Tribe(int unitCount) {
        for (int i = 0; i < unitCount; ++i) {
            _units.push_back(Unit(i));
        }
    }

    void actAll() {
        for (auto& unit : _units) {
            unit.act();
        }
    }
};

