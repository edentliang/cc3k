#include <map>
#include <iostream>
#include "builder.h"
#include <fstream>
#include <sstream>
#include <string>
using namespace std;


Builder::Builder() : colour{""}, score {0} {
    //map <string, int> mysource;
    mySource["Brick"]=0;
    mySource["Energy"]=0;
    mySource["Glass"]=0;
    mySource["Heat"]=0;
    mySource["Wifi"]=0;
    //map<int, string> myRes;
    my["B"] = "Basement";
    my["H"]= "House";
    my["T"] ="Tower";
    cap["Brick"] = "B";
    cap["Energy"]="E";
    cap["Glass"]="G";
    cap["Heat"]="H";
    cap["Wifi"]="W";
}

string Builder::myColour() {
    return colour;
}

int Builder::myScore() {
    return score;
}
void Builder::bug2() {
    score =10;
}

void Builder::setInfo(int k) {
    if (k==0){
        colour = "Blue";
    } else if (k==1) {
        colour ="Red";
    } else if (k==2){
        colour ="Orange";
    } else {
        colour = "Yellow";
    }
}

void Builder::loadInfo(string line) {
    int k;
    stringstream ss{line};
    for (auto &it : mySource) {
        ss >> k;
        it.second = k;
    }
}

string Builder::save() {
    string s;
    for (auto &it : mySource) {
        stringstream ss;
        ss << (it.second);
        string str = ss.str();
        s.append (str);
        s.append (" ");
    }
    s.append("r ");
    for (auto &it : myRoad) {
        stringstream ss;
        ss << it;
        string str = ss.str();
        s.append (str);
        s.append (" ");
    }
    s.append("h ");
    for (auto &it : myRes) {
        stringstream ss;
        ss << it.first;
        string str = ss.str();
        s.append(str);
        s.append(" ");
        s.append(it.second);
    }
    return s;
}

void Builder::status (){
    cout << myColour() << " has "<< myScore() <<" building points, ";
    for (auto& it: mySource) {
        if (it.first == "Wifi") {
            cout << "and "<< it.second << " Wifi."<< endl;
        } else {
            cout << it.second << " " << it.first << ", ";
        }
    }
    cout << myColour() << " has built: "<<endl;
    for (auto &it: myRes) {
        cout << it.first << " "<< it.second <<endl;
    }
    cout <<endl;
}

void Builder::printRes() {
    cout << myColour() << " has built: "<<endl;
    for (auto &it: myRes) {
        cout << it.first << " "<< it.second<<endl;;
    }
    cout <<endl;
}

int Builder::getMySource(string resources) {
    return mySource[resources];
}

bool Builder::canIBuildIt(string houseType) {
    if (houseType == "B") {
        if (mySource["Brick"]>=1 && mySource["Energy"]>=1 && mySource["Glass"]>=1 && mySource["Wifi"]>=1) {
            return true;
        } else {
            return false;
        }
    } else if (houseType == "H") {
        if (mySource["Glass"]>=2 && mySource["Heat"]>=3) {
            return true;
        } else {
            return false;
        }
    } else if (houseType == "T") {
        if (mySource["Brick"]>=3 && mySource["Energy"]>=2 && mySource["Glass"]>=2 && mySource["Wifi"]>=1 && mySource["Heat"]>=2) {
            return true;
        } else {
            return false;
        }
    } else {
        if (mySource["Wifi"]>=1 && mySource["Heat"]>=1) {
            return true;
        } else {
            return false;
        }
    }
}

void Builder::setRes(int posNum,string houseType){
    myRes[posNum]=houseType;
    score +=1;
}

void Builder::setRoad(int posNum) {
    myRoad.emplace_back(posNum);
}

void Builder::improve(int posNum) {
    if (myRes[posNum]=="B") {
        myRes[posNum]="H";
    } else {
        myRes[posNum]="T";
    }
    score +=1;
}

void Builder::addSource(int num, string sourceType) {
    mySource[sourceType] += num;
    
}


void Builder::removeSource(string loseType) {
    int sign =0;
    if (loseType == "geese") {
        int num=0;
        for (auto &it : mySource) {
            if (it.second >=10) {
                ++num;
            }
        }
        
        cout << "Builder "<< myColour() << " loses " << num << " resources to the geese. They lose:"<<endl;;
        
        for (auto &it :mySource) {
            if (it.second >=10) {
                int ori = it.second/2;
                it.second -=ori;
                cout << (ori) << " " << it.first<<endl;
                sign =1;
            }
        }
        if (sign ==0) {
            cout << "nothing."<<endl;
            cout <<endl;
        }
    } else if ( loseType == "B") {
        mySource["Brick"]-=1;
        mySource["Energy"]-=1;
        mySource["Glass"]-=1;
        mySource["Wifi"]-=1;
    } else if (loseType== "H") {
        mySource["Glass"]-=2;
        mySource["Heat"]-=3;
    } else if (loseType == "T") {
        mySource["Brick"]-=3;
        mySource["Energy"]-=2;
        mySource["Glass"]-=2;
        mySource["Wifi"]-=1;
        mySource["Heat"]-=2;
    } else if (loseType == "R") {
        mySource["Wifi"]-=1;
        mySource["Heat"]-=1;
    } else {
        mySource[loseType]-=1;
    }
}


void Builder::geese() {
    removeSource("geese");
}

void Builder::trade(Builder *builder,string source1, string source2) {
    mySource[source1]-=1;
    mySource[source2]+=1;
    builder->removeSource(source2);
    builder->addSource(1, source1);
}

string Builder::stealSource() {
    int sum;
    for (auto &it : mySource) {
        sum += it.second;
    }
    int sum_t;
    map <string, double> steal;
    for (auto &it :mySource) {
        sum_t += it.second;
        steal[it.first]=sum_t/sum;
    }
    double val =rand()/ RAND_MAX;
    string s;
    if (val < steal["Brick"]){
        s = "Brick";
    } else if (val <steal["Energy"]) {
        s= "Energy";
    } else if (val < steal["Glass"]) {
        s ="Glass";
    } else if (val < steal ["Heat"]) {
        s ="Heat";
    } else {
        s="Wifi";
    }
    return s;
}

string Builder::whatOnThere(int posNum) {
    return myRes[posNum];
}

string Builder::myhouseType(int pos) {
    return myRes[pos];
}

bool Builder::doYouhave(int pos) {
    for (auto &it : myRes) {
        if (it.first == pos ) {
            return true;
        }
    }
    return false;
}
