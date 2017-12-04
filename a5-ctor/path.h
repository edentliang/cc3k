#ifndef _PATH_H_
#define _PATH_H_
#include <vector>
#include <string>
#include "subject.h"
#include "observer.h"
#include "subscriptions.h"
#include "address.h"
#include "builder.h"

class Path: public Subject, public Observer {
    Builder*  whoOwn;
    int PosNum;
public:
    Path();
    ~Path();
    
    void setPos(int k);
    void setOwner(Builder* b);
    bool myNeighbourpos(int pos);
    std::string whatOnThere() override;
    std::string belongTo() override;
    SubscriptionType subType() const override;
    int myPos() override;
    void notify(Observer *o) override;
    void buildRoad(Builder *owner);
    void initRoad(Builder *onwer);
};

#endif /* path_h */
