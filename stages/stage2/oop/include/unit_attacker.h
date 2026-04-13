#ifndef __attack_reciever__
#define __attack_reciever__

class Warrior;
class Worker;

// Pattern Visior(double dispatch).
// Instead of one call with switch-case, two consecutive calls are used,
// so no need to change written methods to add new target type.
// Scheme:
// target.acceptAttack(attacker) when unit attacks,
// then in target class: attacker.AttackWarrior(target) or
// attacker.AttackWorker(target), depending on the type
class UnitAttacker {
public:
    virtual void attackWarrior(Warrior& target) = 0;
    virtual void attackWorker(Worker& targer) = 0;
    virtual ~UnitAttacker() = default;
};

#endif