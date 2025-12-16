#ifndef KEY_H
#define KEY_H
#include "entity.h"

class Key : public Entity {
public:
    Key(int x,int y): Entity(x,y){}
    void update(Map& Map) override{}
    char getSymbol() const override {return 'K';}
};

#endif
