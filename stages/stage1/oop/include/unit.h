#ifndef __unit__
#define __unit__

class Unit {
public:
    int id;

public:
    Unit(int id);
    virtual void act() = 0;
    virtual ~Unit() = default;
};

#endif // __unit__