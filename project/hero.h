#ifndef HERO_H
#define HERO_H

#include "entity.h"
#include <vector>

using namespace std;

class Hero: public Entity{
private:

    char symbol_;
    vector<vector<bool>> visited_;
    bool hasKey_;
    bool trapped_;
public:
    Hero(int x,int y,char s): Entity(x,y),symbol_(s),hasKey_(false),trapped_(false){}
    char getSymbol() const override {return symbol_;}
    void update(Map& map) override;
    bool isTrapped() const{return trapped_;}
    bool has_key() const{return hasKey_;}
    void pickKey(){hasKey_=true;}
    void trap() {trapped_=true;}
    void rescue(){trapped_=false;}

};
#endif
