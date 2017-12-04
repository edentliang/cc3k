#include <iostream>
#include <utility>
#include <string>
#include <iostream>
#include <random>
#include <map>
#include "graphicDisplay.h"
using namespace std;

const int spacePerTile = 10;
const int linesHalfTile = 4;
const int spacePerPoint = 4;
const int sizeofBoard = 5;

GraphicDisplay::GraphicDisplay(){
    Geese=0;
}
void GraphicDisplay::initialBoard(int *n){
   
    int cLine = linesHalfTile * sizeofBoard * 2;
    int cPoint = 0;
    int cPath = 0;
    int cTile = 0;
    int cN=0;
    int cc=1;

    for (int i = 0; i <= cLine; i++) {
        vector<char> temp(spacePerTile * sizeofBoard + spacePerPoint, ' ');
        int j = 0;
        int startPos = 0;
        int endPos = spacePerTile * sizeofBoard + spacePerPoint;
        if (i < linesHalfTile || i > cLine - linesHalfTile) {
            startPos = spacePerTile * 2;
            endPos = spacePerTile * 3 + spacePerPoint;
        } else if ((i >= linesHalfTile && i < linesHalfTile * 2) ||
                   (i > cLine - linesHalfTile * 2 && i <= cLine - linesHalfTile)) {
            startPos = spacePerTile;
            endPos = spacePerTile * 4 + spacePerPoint;
        }
        for (j = startPos; j < endPos; j++) {
            if ((i % 8 == 0 && j % 20 == 6) || (i % 8 == 4 && j % 20 == 16) ||
                (i % linesHalfTile == 2 && j % spacePerTile == 1)) {
                if (i % 4 == 0) {
                    temp.at(j - 2) = '-';
                    temp.at(j - 1) = '-';
                    temp.at(j + 2) = '-';
                    temp.at(j + 3) = '-';
                }
                if (cPath < 10) {
                    temp.at(j+1) = '0' + cPath;
                } else {
                    temp.at(j) = '0'+cPath/10;
                    temp.at(j+1) = '0' + cPath % 10;
                }
                pair<int,int> p;
                p = make_pair(i,j);
                roadKeys.push_back(p);
                j++;
                cPath++;
            } else if ((i % 8 == 2 && j % 20 == 6) || (i % 8 == 6 && j % 20 == 16)) {
                if (cTile < 10) {
                    temp.at(j+1) = '0' + cTile;
                } else {
                    temp.at(j) = '0'+ cTile/10;
                    
                    temp.at(j+1) = '0' + cTile % 10;
                }
                pair <int,int> p;
                p = make_pair(i,j);
                tileKeys.push_back(p);
                j++;
                cTile++;
            }else if ((i % 8 == 3 && j % 20 == 5) || (i % 8 == 7 && j % 20 == 15)) {
                string s;
                if (n[cN] == 0) {
                            s.append("BRICK");
                        } else if (n[cN] == 1) {
                            s.append("ENERGY");
                        } else if (n[cN] == 2) {
                            s.append("GLASS");
                        } else if (n[cN] == 3) {
                            s.append("HEAT");
                        } else if (n[cN] == 4) {
                            s.append("WIFI");
                        } else if (n[cN] == 5) {
                            s.append("PARK");
                        }
                    for (unsigned int l = 0; l < s.length(); l++) {
                        temp.at(j) = s[l];
                        j++;
                    }
                cN+=2;
            } else if ((i % 8 == 0 && j % 20 == 16) || (i % 8 == 4 && j % 20 == 6)) {
                if (n[cc]==7){
                    
                }else if (n[cc] < 10) {
                            j++;
                            temp.at(j) = '0' + n[cc];
                        } else {
                            temp.at(j) = '0'+ n[cc]/10;
                            j++;
                            temp.at(j) = '0' + n[cc] % 10;
                        }
                cc+=2;
            }  else if (i % 2 == 1 && j % spacePerTile == 2) {
                temp.at(j) = '|';
            } else if (i % linesHalfTile == 0) {
                if (j % spacePerTile == 0 || j % spacePerTile == 3) {
                    temp.at(j) = '|';
                } else if (j % spacePerTile == 1) {
                    if (cPoint < 10) {
                        
                        temp.at(j+1) = '0' + cPoint;

                    } else {
                        temp.at(j) = '0'+cPoint/10;
                        
                        temp.at(j+1) = '0' + cPoint % 10;
                    }
                    pair <int,int> p;
                    p=make_pair(i,j);
                    adKeys.push_back(p);
                    cPoint++;
                    j++;
                }
            }
        }
        Board.push_back(temp);
        }
        //delete[] n;

}



void GraphicDisplay::setHouseType(string bName,string hType, int ad) {
    int row,col;
    //cout << "here"<<endl;
    row=(adKeys.at(ad)).first;
    col=(adKeys.at(ad)).second;
    Board[row][col]=bName[0];
    //cout << row << " " << col << " " << Board[row][col] <<endl;
    Board[row][col+1]=hType[0];
    //cout << *this;
}

void GraphicDisplay::setRoad(string bName, int n){
    int row,col;
    row=(roadKeys.at(n)).first;
    col=(roadKeys.at(n)).second;
    Board[row][col]=bName[0];
    Board[row][col+1]='R';
}

/* int* GraphicDisplay::randomResources(){
    int index,tmp,i;
    int a[19]= {2,3,3,4,4,5,5,6,6,7,8,8,9,9,10,10,11,11,12};
    int b[19]= {0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,4,4,4,5};
    srand(time(NULL));
    for(i=0;i<19;i++){
        index=rand()%(19-i)+i;
        if(index!=i){
            tmp=a[i];
            a[i]=a[index];
            a[index]=tmp;
        }
    }
    for(i=0;i<19;i++){
        index=rand()%(19-i)+i;
        if(index!=i){
            tmp=b[i];
            b[i]=b[index];
            b[index]=tmp;
        }
    }
    int *n = new int[38];
    int k = 0;
    for(i=0;i<19;i++){
        n[k] = b[i];
        k++;
        n[k] = a[i];
    }
}
*/

void GraphicDisplay:: geesePos(int num){
    //erase GEESE at previous position
    int row,col;
    row=(tileKeys.at(Geese)).first;
    col=(tileKeys.at(Geese)).second;
    row+=3;
    col--;
    for(int i = 0;i<5;i++){
        Board[row][col+i]=' ';
    }
    // move GEESE to num
    Geese=num;
    row=(tileKeys.at(Geese)).first;
    col=(tileKeys.at(Geese)).second;
    string s;
    s.append("GEESE");
    row+=3;
    col--;
    for(int i = 0;i<5;i++){
        Board[row][col+i]=s[i];
    }
}//找错位置

GraphicDisplay::~GraphicDisplay() {
}

void GraphicDisplay::clean(){
    adKeys.clear();
    roadKeys.clear();
    tileKeys.clear();
    for (int i=0;i<=40;i++){
        Board[i].clear();
    }
    Board.clear();
    Geese  = 0;
}

string GraphicDisplay::whatOnThere() {
    return "";
}
string GraphicDisplay::belongTo() {
    return "";
}
int GraphicDisplay::myPos() {
    return 0;
}

ostream &operator<<(ostream &out, GraphicDisplay &gd) {
    for(int i = 0; i <=linesHalfTile * sizeofBoard * 2; i++){
        for(int j=0;j<spacePerTile * sizeofBoard + spacePerPoint;j++){
            out << gd.Board[i][j];
        }
        out<<endl;
    }
    return out;
}

SubscriptionType GraphicDisplay::subType() const {
    return SubscriptionType::GD;
}

void  GraphicDisplay::notify(Observer *o) {
    
    if (o->subType() == SubscriptionType::Path){
        setRoad(o->belongTo(), o->myPos());
    } else {
        setHouseType(o->belongTo(), o->whatOnThere(), o->myPos());
    }
}
