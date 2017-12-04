#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include "subscriptions.h"
#include <string>
class Observer;

class Subject {
    std::vector<Observer*> observers;
    int size;
   public:
    Subject();
    
    void attach(Observer *o);
    bool myNeighbourPos(int posNum);
    bool canIBuild(std::string who,int k);
    bool neighbourOwner(std::string who) ;
    bool noOneOwnButMe(std::string who);
    bool BelondOthers(std::string who);
    
    //bool myPos(int posNum);//for tile, find address
    //void notifyObservers(SubscriptionType t);
    
    void notifyB_Gd(Observer *o, SubscriptionType Type);
    virtual ~Subject() = 0;
    
};

#endif /* subject_h */
