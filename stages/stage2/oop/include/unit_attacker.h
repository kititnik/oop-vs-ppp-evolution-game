#ifndef __attack_reciever__
#define __attack_reciever__

class Warrior;
class Worker;

class UnitAttacker {
public:
    virtual void attackWarrior(Warrior& target) = 0;
    virtual void attackWorker(Worker& targer) = 0;
    virtual ~UnitAttacker() = default;
};

#endif