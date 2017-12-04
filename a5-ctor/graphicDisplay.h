#ifndef PROJECTS_GRAPHICDISPLAY_H
#define PROJECTS_GRAPHICDISPLAY_H
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "observer.h"

class GraphicDisplay:public Observer {
    std::vector<std::vector<char>> Board;
    //int *boardLayout;
    int Geese;
    std::vector<std::pair<int,int>> roadKeys,tileKeys,adKeys;

public:
    GraphicDisplay();

    ~GraphicDisplay();
    void clean();
    void initialBoard(int* n);
    void setHouseType (std::string bName,std::string hType, int ad);
    void setTile (std::string bName, int ad);
    void setRoad (std::string bName, int ad);
    void geesePos(int num);
    
    
    std::string whatOnThere() override;
    std::string belongTo() override ;
    int myPos() override;

    SubscriptionType subType() const override;
    void notify(Observer *o) override;
    
    friend std::ostream &operator<<(std::ostream &out, GraphicDisplay &td);
};


#endif //PROJECTS_GRAPHICDISPLAY_H
