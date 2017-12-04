#ifndef _TILE_H_
#define _TILE_H_
#include "observer.h"
#include "builder.h"
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include "address.h"
class Builder;

class Tile {
    std::vector<Observer*> v;
    std::vector<Builder*> b;
    int bSize;
    int posNum;
    std::string source;
    std::map<int, std::string> resourceList;
    int sour;
    int diceNum;
    public:
    Tile();
    ~Tile();
    
    bool isIn (int pos);
    void attach(Observer* o);
    void setBuilder(Builder* b);
    void setPos(int k);
    void whoGainWhat();
    void setSour(int k);
    void setDice(int k);
    int myDice();
    
    bool SomeoneOnTile();
    void whoOnTile(std::string me);
    void steal(std::string who);
    void geese();
    
};

#endif /* tile_h */
