#include <stdio.h>
#include "address.h"

using namespace std;
Address::Address(): owner(nullptr), houseType(""), PosNum(-1) {}

Address::~Address() {
    }

/*void Address::setNeigh(Address *a) {
    neighbour.emplace_back(a);
}*/

void Address::setPos(int k) {
    PosNum = k;
}

void Address::setOwner(Builder *bowner) {
    owner = bowner;
}
void Address::setHouseType(string type) {
    houseType = type;
}

string  Address::whatOnThere() {
    return houseType;
}

string Address::belongTo() {
    if (owner == nullptr) {
        return "noOne";
    } else {
        return owner->myColour();
    }
}

SubscriptionType Address::subType() const  {
    return SubscriptionType::Address;
}

int Address::myPos() {
    return PosNum;
}

void Address::notify(Observer *o ) {}
                     
void Address::initBuild(Builder *builder,string type) {
    owner = builder;
    houseType = type;
    owner->setRes(PosNum, type);
    notifyB_Gd(this, SubscriptionType::GD);
}

void Address::buildRes(Builder *bowner) {
    owner  = bowner;
    houseType = "B";
    owner->setRes(PosNum, "B");
    owner->removeSource("B");
    notifyB_Gd(this, SubscriptionType::GD);
}

void Address::improve() {
    if (houseType == "B") {
        houseType = "H";
    } else {
        houseType ="T";
    }
    owner->improve(PosNum);
    owner->removeSource(houseType);
    notifyB_Gd(this, SubscriptionType::GD);
}

/*bool Address::canI(string c,int k) {
    if (canIBuild(c,k)) {
        for (auto &it: neighbour) {
            if (it->belongTo() != c && it->belongTo() !="noOne"){
                return false;
            }
        }
        return true;
    }
    return false;
}*/
