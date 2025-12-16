#include "hero.h"
#include <iostream>

using namespace std;

void Hero::update(Map &map){
    if(trapped_)return;

    int w=map.GetWidth();
    int h=map.GetHeight();
    if(visited_.empty())
        visited_.assign(h,vector<bool>(w,false));
    visited_[getY()][getX()]=true;

    static const int DX[4]={1,-1,0,0};

    static const int DY[4]={0,0,1,-1};

    int start=rand()%4;

    vector<int>dirs ={0,1,2,3};

  for(int i=0;i<4;++i){
        int d=(start+i)%4;
        int nx=getX()+DX[d];
         int ny=getY()+DY[d];
         if(nx>=0 && nx<w && ny>=0 && ny<h && !map.isWall(nx,ny)){
             setX(nx);
             setY(ny);
             visited_[ny][nx]=true;
             break;
        }
    }
}
