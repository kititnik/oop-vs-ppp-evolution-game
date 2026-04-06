#ifndef __unit__
#define __unit__

struct SimuationContext;

class Unit {
protected:
    int _id;
    int _health;

public:
    Unit(int id);
    virtual void act(SimuationContext& context) = 0;
    bool isAlive();
    void takeDamage(int damage);
    int getHealth();
    int getId();
    virtual ~Unit() = default;
};

#endif // __unit__