#ifndef _ADDRESS_H_
#define _ADDRESS_H_
#include <vector>
#include <string>
#include "subject.h"
#include "observer.h"
#include "subscriptions.h"
#include "path.h"
#include "builder.h"

class Address: public Subject, public Observer {
    Builder *owner;
    std::string houseType;
    int PosNum;
    //std::vector<Address*> neighbour;
public:
    Address();
    ~Address();
    
    void setPos(int k);
    void setOwner(Builder *owner);
    void setHouseType(std::string type);
    
    //void setNeigh(Address *a);
    std::string whatOnThere() override;
    std::string belongTo() override ;
    int myPos() override;
    SubscriptionType subType() const  override ;
    void notify(Observer *o) override;
    
    //bool canI(std::string c,int k);
    void buildRes(Builder *owner);
    void initBuild(Builder *bulider, std::string type);
    void improve();

};
#endif /* address_h */
