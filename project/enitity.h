#ifndef ENTITY_H
#define ENTITY_H


#include "map.h"

class Entity {
private:
    int x_;
    int y_;
protected:
    void setX(int x){x_=x;}
    void setY(int y){y_=y;}
public:
    Entity(int x,int y):x_(x),y(_y){
    virtual ~Entity()= default;

    int getX() const {return x_;}
    int getY() const {return y_;}

    virtual void update(Map& map)=0;

    virtual char getSymbol() const=0;
    }
};

#endif
