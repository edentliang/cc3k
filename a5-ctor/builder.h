#ifndef _BUILDER_H_
#define _BUILDER_H_
#include <map>
#include <vector>
#include <string>

#include "observer.h"




class Builder {
    std::string colour;
    int score;
    std::map<std::string, int> mySource;
    //Sources mySources;
    std::map<int, std::string> myRes;
    std::vector<int> myRoad;
    std::map<std::string, std::string> my;
    std::map<std::string, std::string> cap;
public:
    Builder();
    
    std::string myColour();
    int myScore();
    void setInfo(int k);
    //void setMap();//in setInfo
    void bug2();
    //SubscriptionType subType() const  override;
    void loadInfo(std::string);
    void setRes(int posNum, std::string houseType);
    void setRoad(int posNum);
    void improve(int posNum);
    std::string myhouseType(int posNum);
    void status();
    void printRes();
    std::string save();
    int getMySource(std::string resources);
    bool canIBuildIt(std::string HouseType);
    std::string  whatOnThere(int posNum);
    void addSource(int num, std::string sourceType);//trade, gain 
    void removeSource(std::string loseType);//include geese, trade  and steal
    void geese();
    //void notify(Observer *o) override;
    void trade (Builder* builder, std::string source1, std::string source2);
    std::string stealSource();
    bool doYouhave(int pos);
};

#endif /* builder_h */
