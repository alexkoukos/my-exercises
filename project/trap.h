#ifndef CAGE_H
#define CAGE_H
#include "entity.h"


class Trap : public Entity {
private:
    bool triggered_=false;
public:
    Trap(int x,int y) : Entity(x,y){}
    void update(Map& map) override{}
    void trigger(){triggered_=true;}
    bool isTriggered() const {return triggered_;}
    char getSymbol() const override {return triggered_ ? 'C' : 'T'; }


};
#endif
