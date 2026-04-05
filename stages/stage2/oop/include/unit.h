#ifndef __unit__
#define __unit__

class Unit {
protected:
    int _id;
    int _health;

public:
    Unit(int id);
    virtual void act() = 0;
    bool isAlive();
    void takeDamage(int damage);
    int getHealth();
    virtual ~Unit() = default;
};

#endif // __unit__