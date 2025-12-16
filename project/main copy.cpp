#include <iostream>
#include <vector>
#include <memory>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <random>
#include <ncurses.h>

#include "map.h"
#include "entity.h"
#include "hero.h"
#include "trap.h"
#include "key.h"


using namespace std;




int main(int argc, char* argv[]) {

    if (argc<2) {
        cerr << "Χάρτης" << argv[0] << " <map1.txt>\n";
        return -1;
    }

     srand((unsigned)time(nullptr));

    Map maze;
    if (!maze.loadFromFile(argv[1])) {
        cerr << "Απέτυχε το άνοιγμα του χάρτη " << argv[1] << "\n";
        return -1;
    }

    vector<Position> walls;
    for(int y=0;y<maze.GetHeight();++y){
        for(int x=0; x<maze.GetWidth();++x){
            if(maze.isWall(x,y))
                walls.emplace_back(x,y);
            }
        }

int w=maze.GetWidth();
int h=maze.GetHeight();


    initscr();
    noecho();
    cbreak();
    curs_set(0);
    nodelay(stdscr,TRUE);


    mvprintw(0,0, "Χάρτης %dx%d φορτώθηκε. Πατήστε οποιοδήποτε πλήκτρο για εκκίνηση...",
             maze.GetWidth(),maze.GetHeight());
    refresh();
    getch();



            vector<pair<int,int>> used;

        auto placeEntity=[&](int &ex,int &ey,int ox,int oy){
       do{
            ex=rand()%w;
            ey=rand()%h;
        } while(maze.isWall(ex,ey)||find(used.begin(),used.end(),make_pair(ex,ey)) !=used.end() || (ox>=0 && oy>=0 && abs(ex-ox)+ abs(ey-oy)<7));
            used.emplace_back(ex,ey);
};


    vector<unique_ptr<Entity>> ents;

    int x1,y1;
    placeEntity(x1,y1,-1,-1);
    ents.emplace_back(make_unique<Hero>(x1,y1,'G'));

    int x2,y2;
    placeEntity(x2,y2,x1,y1);
    ents.emplace_back(make_unique<Hero>(x2,y2,'S'));

    int kx,ky;
    placeEntity(kx,ky,-1,-1);

        ents.emplace_back(make_unique<Key>(kx,ky));

    int tx1,ty1;
        placeEntity(tx1,ty1,-1,-1);
        ents.emplace_back(make_unique<Trap>(tx1,ty1));
    int tx2,ty2;
        placeEntity(tx2,ty2,-1,-1);
        ents.emplace_back(make_unique<Trap>(tx2,ty2));


        Hero* h1=dynamic_cast<Hero*>(ents[0].get());
        Hero* h2=dynamic_cast<Hero*>(ents[1].get());
        Key* key=dynamic_cast<Key*>(ents[2].get());
        Trap* t1 =dynamic_cast<Trap*>(ents[3].get());
        Trap* t2 =dynamic_cast<Trap*>(ents[4].get());

        Position stair=maze.findStair();




        bool met=false;
        bool clearing=true;
        bool done=false;
        size_t remI=0;
        vector <Position> path;
        size_t pI=0;
        const int maxtermina=1000;





                   for(int turn=1;turn<=maxtermina && !done;++turn){
                            for(auto& e: ents) {
                                e->update(maze);
                            }
                   for(Hero* hero:{h1,h2}){
                       if(!hero->isTrapped()){
                           int hx=hero->getX();
                           int hy=hero->getY();
                           for(Trap* trapPtr:{t1,t2}){
                               if(trapPtr->getX()==hx&& trapPtr->getY()==hy &&!trapPtr->isTriggered()){
                                   if(!hero->has_key()){
                                       trapPtr->trigger();
                                       hero->trap();
                                }
                                break;
                            }
                        }
                    }
                }



                if(!h1->has_key()&& h1->getX()==key->getX()&& h1->getY()==key->getY())
                    h1->pickKey();

                if(!h2->has_key()&& h2->getX()==key->getX()&& h2->getY()==key->getY())
                    h2->pickKey();

                  if(h1->isTrapped()&& h2->has_key() && h1->getX()==h2->getX() && h1->getY()==h2->getY())
                    h1->rescue();


                         if(h2->isTrapped()&& h1->has_key() && h2->getX()==h1->getX() && h2->getY()==h1->getY())
                    h2->rescue();


                       if(turn==maxtermina && !met){
                           mvprintw(h+2,0,"Τέλος χρόνου! Game Over!");
                           done=true;
                    }

                    if(h1->isTrapped() && h2->isTrapped() ){
                         mvprintw(h+2,0,"Οι δύο ήρωες παγιδεύτηκαν! Game Over!");
                           done=true;
                    }

                    if(!met &&
                        ((h1->getX() == h2->getX() && h1->getY() == h2->getY())||
                        (h2->getX()==h1->getX() && h2->getY() ==h1->getY())))
                        {
                            met=true;
                            done=true;
                            mvprintw(h+2,0,"Οι δύο ήρωες συναντήθηκαν! Νίκη!");
                            refresh();
                            napms(1000);
                            break;
                        }
                       if(met){
                       if(clearing){
                           if(remI<walls.size()){
                               auto p=walls[remI++];
                               maze.setCell(p.x,p.y,CellType::Floor);
                        }
                        else{
                            clearing=false;
                        } }
                        else if(pI<path.size()){
                                auto nxt=path[pI++];
                            h1->setX(nxt.x);
                            h1->setY(nxt.y);
                            h2->setX(nxt.x);
                            h2->setY(nxt.y);
                        }else{
                            mvprintw(h+2,0,"Έφτασαν στην σκάλα! Happy End!");
                            done=true;
                        }
                       }
            clear();
            for(int yy=0;yy<maze.GetHeight();++yy){
                for(int xx=0;xx<maze.GetWidth();++xx){
                    char ch = ' ';
                    int c = maze.getCell(xx,yy);
                    if(c==CellType::Wall)
                        ch='*';
                    else if(c==CellType::Stair)
                        ch='L';
                    mvaddch(yy ,xx, ch);
                    }
            }
                    for(auto& e: ents)
                        mvaddch(e->getY(),e->getX(),e->getSymbol());





            mvprintw(h+1,0,"---- Termina %d -----", turn);
            refresh();
            napms(150);
                   }

               endwin();

 return 0;}
