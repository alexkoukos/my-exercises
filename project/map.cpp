#include "map.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdexcept>



constexpr int CellType::Wall;
constexpr int CellType::Floor;
constexpr int CellType::Stair;

using namespace std;

bool Map::loadFromFile(const string& filename) {
    ifstream in(filename);
    if (!in.is_open()) return false;

    vector<string> lines;
    string line;
    while (getline(in,line))
        lines.push_back(line);
    in.close();
    height = lines.size();
    width = 0;
    for (auto& l:lines)
            width = max(width,(int)l.size());
        grid.assign(height, vector<int>(width,CellType::Floor));
    for (int y=0; y < height; ++y){
        for (int x=0; x < width; ++x){
            char c = (x< (int)lines[y].size() ? lines[y][x] : ' ');
            if (c == '*') grid[y][x] = CellType::Wall;
            else if (c == 'L') grid[y][x] = CellType::Stair;
            else grid[y][x] = CellType::Floor;

        }
    }
    return true;
}

int Map::getCell(int x, int y) const {
    if (x < 0 || x>= width || y < 0 || y >= height)
        throw out_of_range("Map::getCell:is out of range");
    return grid[y][x];

}


Position Map::findStair()const{
    for (int y=0; y<height;++y){
        for(int x=0;x<width;++x){
            if(grid[y][x]==CellType::Stair)
                return Position(x,y);
        }

    }
    return Position(-1,-1);
}



vector<Position> Map::findPath(const Position& start,const Position& goal) const{
   auto inBounds=[&](int x,int y){
       return x>=0 && x<width && y>=0 && y<height;
};
auto isPassable=[&](int x,int y){
    return !isWall(x,y);
};
  auto heuristic=[&](const Position &a, const Position &b){
       return abs(a.x-b.x)+abs(a.y-b.y);
  };

  struct Node{
      Position p;
      int g;
      int f;

};
  struct Cmp{
      bool operator()(Node const &a, Node const &b)const {
      return a.f>b.f;
}

};

    priority_queue<Node,vector<Node>,Cmp> open;
    map <Position,Position> cameFrom;
    map <Position,int> gScore;
    map <Position,int> fScore;

    gScore[start]=0;
    fScore[start]=heuristic(start,goal);
    open.push({start,0,fScore[start]});


    static const int DX[4] = {1,-1,0,0};
    static const int DY[4] = {0,0,1,-1};

    while(!open.empty()){
        Node node = open.top();
            open.pop();
            Position cur=node.p;
            if(cur ==goal){
                vector<Position> path;
                for(Position p=goal;!(p==start);p=cameFrom[p])
                    path.push_back(p);
                reverse(path.begin(),path.end());
                return path;
            }
            for(int i=0;i<4;++i){
                int nx =cur.x+DX[i];
                int ny =cur.y+DY[i];
                if(!inBounds(nx,ny)|| isWall(nx,ny))continue;
                Position nbr(nx,ny);
                int tentative_g=gScore[cur]+1;
                if(!gScore.count(nbr)||tentative_g<gScore[nbr]){
                    cameFrom[nbr]=cur;
                    gScore[nbr]=tentative_g;
                    fScore[nbr]=tentative_g+heuristic(nbr,goal);
                    open.push({nbr,gScore[nbr],fScore[nbr]});
                }
            }
    }
    return {};
}



