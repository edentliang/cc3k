#ifndef _board_h
#define _board_h
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <utility>

#include "builder.h"
#include "path.h"
#include "address.h"
#include "tile.h"
#include "graphicDisplay.h"

class Board  {
    int whoseTurn;
    std::map<std::string, int> builderColour;
    std::vector<Builder> builderList;
    std::vector<Path> allPath;
    int pathsize;
    std::vector<Address> allAddress;
    int addressSize;
    std::vector<Tile> allTile;
    int tileSize;
    GraphicDisplay *gd;
    int seed;
    int *aa;
    int dice;

    
 public:
    Board();
    ~Board();
    
    void initBoard();
    void clean();
    void load(std::string file);
    void loadBoard(std::string file);
    void setNewG();
    void save(std::string file);
    void setSeed(int k);
    int* generateRan();
    void setTile();
    void setTileResource(int* a);
    std::string who();
    
    bool someoneInRes(int pos);
    bool someoneInRoad(int pos);
    void Diceload(int k);//not
    void Dicefair();//not
    void nextTurn();
    void setTurn(int t);
    int myDice();
    bool isWon();
    std::string whoWon();
    void printStatus();
    void printRes();
    void setBug(int k);
    bool someoneOnTile(int pos);
    void steal(std::string w);
    void gainResource();
    bool setInitHouse(int where);
    void buildRoad(int path);
    void buildRes(int address);
    void improve(int address);
    void moveGeese(int posNum);
    void geese();
    void trade (std::string builder, std::string source1, std::string source2);
    void bug2();
    friend std::ostream &operator<<(std::ostream &out, const Board &b);
};


#endif /* board_h */
