#include <stdio.h>
#include "tile.h"
#include <string>

using namespace std;

Tile::Tile() :  bSize(0),posNum(0), source(""),sour(0),diceNum(0){}

void Tile::setPos(int k) {
    posNum = k;
    vector<Builder*> b;
    vector<Observer*> v;
}

Tile::~Tile() {
    v.clear();
}

void Tile::attach(Observer *o) {
    v.emplace_back(o);
}

void Tile::setBuilder(Builder *bb) {
    for (auto &it : b) {
        if (it->myColour() == bb->myColour()) {
            return;
        }
    }
    b.emplace_back(bb);
    bSize+=1;
    //cout << bSize << "!"<< posNum <<endl;
}

bool Tile::isIn(int pos) {
    for (auto &it:v) {
        if (it->subType() == SubscriptionType::Address) {
            if (it->myPos()==pos) {
                return true;
            }
        }
    }
    return false;
}
void Tile::whoGainWhat() {
    for (auto &it :v) {
        if (it->subType() == SubscriptionType::Address) {
            
            for (auto &kk : b) {
                if (kk->doYouhave(it->myPos())){
                string houseType =kk->myhouseType(it->myPos());
                if (houseType == "B") {
                    kk->addSource(1, source);
                    //cout << source <<endl;
                } else if (houseType == "H") {
                    kk->addSource(2, source);
                } else {
                    kk->addSource(3, source );
                }
                }
            }
        }
    }
}

void Tile::setDice(int k) {
    diceNum = k;
}

void Tile::setSour(int k) {
    sour = k;
    if (k==0) {
        source = "Brick";
    } else if (k==1) {
        source = "Energy";
    } else if (k==2) {
        source = "Glass";
    } else if (k==3) {
        source = "Heat";
    } else {
        source = "Wifi";
    }
}

bool Tile::SomeoneOnTile() {
    //cout << bSize<<endl;
    return (bSize !=0);
}

int Tile::myDice() {
    return diceNum;
}
void Tile::whoOnTile(string me) {
    int k=0;
    for (auto &it : b) {
        if (it->myColour()!=me) {
        if ( k == bSize-1){
            cout << it->myColour()<<"."<<endl;
        } else {
            cout << it->myColour() << ", ";
            k+=1;
        }
        } else {
            k+=1;
        }
    }
}

