#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include "subscriptions.h"
#include <string>

class Subject;
class Address;
class Path;
class GraphicDisplay;

class Observer{

public:
    
    virtual std::string whatOnThere()=0;
    virtual std::string belongTo() = 0;
    virtual int myPos()=0;
    //virtual bool neighbourOwner(std::string whoOwn)=0;
    virtual SubscriptionType subType() const = 0;
    virtual void notify(Observer *o) =0;//only gd
    virtual ~Observer() = default;
};

#endif /* observer_h */
