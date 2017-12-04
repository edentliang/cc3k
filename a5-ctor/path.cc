#include <stdio.h>
#include <string>
#include "path.h"
using namespace std;
Path::Path(): whoOwn(nullptr), PosNum(-1) {}

Path::~Path() {
}

void Path::setPos(int k) {
    PosNum = k;
}

void Path::setOwner(Builder *b) {
    whoOwn = b;
}

string Path::whatOnThere() {
    return "";
}
string Path::belongTo() {
    if (whoOwn == nullptr) {
        return "noOne";
    } else {
        return whoOwn->myColour();
    }
}

int Path::myPos() {
    return PosNum;
}

void Path::notify(Observer *o) {
}


SubscriptionType Path::subType() const  {
    return SubscriptionType::Path;
}

void Path::initRoad(Builder *onwer) {
    whoOwn  = onwer;
    whoOwn->setRoad(PosNum);
    notifyB_Gd(this, SubscriptionType::GD);
}

void Path::buildRoad(Builder *owner) {
    whoOwn = owner;
    whoOwn->setRoad(PosNum);
    whoOwn->removeSource("R");
    notifyB_Gd(this, SubscriptionType::GD);
}

bool Path::myNeighbourpos(int pos) {
    return myNeighbourPos(pos);
}
