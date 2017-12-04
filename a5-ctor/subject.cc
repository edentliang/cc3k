#include <stdio.h>
#include "subject.h"
#include <string>
#include "observer.h"
#include <iostream>
#include <string>
using namespace std;

Subject::Subject(): size(0) {
}

Subject::~Subject() {
    observers.clear();
}

void Subject::attach(Observer *o) {
    observers.emplace_back(o);
    size+=1;
}

bool Subject::canIBuild(string who,int p) {
   
    for (int k =0; k<size; ++k) {
        if (observers[k]->subType() == SubscriptionType::Address) {
            if (observers[k]->belongTo() == who){
                return true;
            } else {
                Subject *temp= dynamic_cast<Subject*>(observers[k]);
                if (temp->neighbourOwner(who)) {
                    return true;
                }
            }
        } else if (observers[k]->subType() == SubscriptionType::Path){
            Subject *temp= dynamic_cast<Subject*>(observers[k]);
            if (temp->BelondOthers(who)) {
                //cout << "1"<<endl;
                return false;
            }
        }
    }
    if (observers[0]->subType() == SubscriptionType::Address) {
        return false;
    } else if (p==1){
        return true;
    } else {
        return neighbourOwner(who);
    }
}

bool Subject::neighbourOwner(string who) {
    for (int k =0; k<size; ++k) {
        if (observers[k]->belongTo() == who) {
            return true;
        }
    }
    //cout << "neigh" <<endl;
    return false;
}

bool Subject::BelondOthers(string who) {
    
    for (auto it : observers) {
        if (it->subType() ==SubscriptionType::Address) {
            if ( it->belongTo() != who && it->belongTo() !="noOne") {
                //cout << it->belongTo() << " " << who <<endl;
                return true;
         }
        }
    }
    return false;
}

void Subject::notifyB_Gd(Observer *o, SubscriptionType Type) {
    for (auto &it : observers) {
        if (it->subType() == Type) {
            it->notify(o);
        }
    }
    //cout << "NOTIFY"<<endl;
}

bool Subject::myNeighbourPos(int posNum) {
    for (auto &it :observers) {
        if (it->subType() != SubscriptionType::GD){
        if (it->myPos() == posNum) {
            return true;
        }
        }
    }
    //cout << "neigh" <<endl;
    return false;
}
