#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <queue>
#include <map>
#include <algorithm>
#include <limits>

using namespace std;

class CellType{
public:
   static constexpr int Wall=0;
   static constexpr int Floor=1;
   static constexpr int Stair=2;
};



class Position{
public:
    int x;
    int y;
    Position(int X=0,int Y=0):x(X),y(Y){}
    bool operator==(const Position& o) const {return x==o.x && y==o.y;}
     bool operator<(const Position& o) const {return x!=o.x ? x<o.x : y<o.y;}
};


class Map {
private:
    vector<vector<int>> grid;
    int width = 0;
    int height = 0;
public:
    Map () = default;
    bool loadFromFile(const string& filename);

    int GetWidth() const { return width; }
    int GetHeight() const { return height; }

    int getCell(int x, int y) const;
    void setCell(int x,int y,int val){grid[y][x]=val;}

    bool isWall (int x, int y) const { return getCell(x,y) == CellType::Wall; }
    bool isFloor (int x, int y) const { return getCell(x,y) == CellType::Floor; }
    bool isStair (int x, int y) const { return getCell(x,y) == CellType::Stair; }


    Position findStair() const;
    vector <Position> findPath(const Position& start,const Position& goal)const;

};

#endif
