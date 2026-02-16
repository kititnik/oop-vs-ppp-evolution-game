#include <vector>
#include "unit.h"

class Tribe {
private:
    std::vector<Unit> _units;

public:
    Tribe(int unitCount);
    void actAll();
};

