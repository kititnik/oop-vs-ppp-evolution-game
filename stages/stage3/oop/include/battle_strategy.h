#ifndef __battle_strategy__
#define __battle_strategy__

class Warrior;
class Worker;
struct SimulationContext;

// battle_strategy.h - encapsulates tribe behavior algorithm.
// Different races have different strategies of how their units act.
class BattleStrategy {
public:
    virtual void actWarrior(Warrior& unit, SimulationContext& context) = 0;
    virtual void actWorker(Worker& unit, SimulationContext& context) = 0;
    virtual ~BattleStrategy() = default;
};

#endif // __battle_strategy__
