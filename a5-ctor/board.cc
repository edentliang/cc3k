#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "board.h"
#include <cstdlib>
using namespace std;


Board::Board() : whoseTurn(0), pathsize(72), addressSize(54),tileSize(19), gd(nullptr), seed(0), aa{nullptr}, dice(0){
    //map<string, int> builderColour;
    builderColour["Blue"]=0;
    builderColour["Red"]=1;
    builderColour["Orange"]=2;
    builderColour["Yellow"]=3;

}

void Board::initBoard() {
    clean();
    
    aa=generateRan();
    gd= new GraphicDisplay;
    
        //vector<Builder> builderList;
    for (int k =0; k< 54; ++k){
        Address a;
        a.setPos(k);
        allAddress.emplace_back(a);
    }
   // vector<Address> allAddress;
    for (int k=0; k < 4; ++k){
        Builder b;
        b.setInfo(k);// need gd
        builderList.emplace_back(b);
    }
    
    //vector<Path> allPath;
    for (int k =0; k< 72; ++k) {
        Path pt;
        pt.setPos(k);
        if (k==0) {
            pt.attach(&allAddress[0]);
            pt.attach(&allAddress[1]);	
        } else if ( k == 71) {
            pt.attach(&allAddress[52]);
            pt.attach(&allAddress[53]);
        
        } else if ( k ==69 || k ==70) {
            int m = k-20;
            pt.attach(&allAddress[m]);
            pt.attach(&allAddress[m+3]);
            
        } else if (k==1 || k==2) {
            pt.attach(&allAddress[k-1]);
            pt.attach(&allAddress[k+2]);
            
        } else if (k== 3|| k ==4 ) {
            int m= (k-2)*2;
            pt.attach(&allAddress[m]);
            pt.attach(&allAddress[m+1]);
        } else if (k ==67 || k ==68) {
            int m = (k-67)*2+48;
            pt.attach(&allAddress[m]);
            pt.attach(&allAddress[m+1]);
        } else if (k>=5 && k<=8) {
            int m = k-3;
            pt.attach(&allAddress[m]);
            pt.attach(&allAddress[m+5]);
        } else if ( k>=63 && k<=66) {
            int m = k-20;
            pt.attach(&allAddress[m]);
            pt.attach(&allAddress[m+5]);
        
        } else if ((k-9)%17 <= 2 && k>=9) {
            int m = (k/17)+1;
            int n = ((k-9)%17)*2;
            pt.attach(&allAddress[6*m+n]);
            pt.attach(&allAddress[6*m+n+1]);
        } else if ((k-18)%17 <= 1 && k>=18) {
            int m= (k/17)*12 +1;
            int n = (k-18)%17*2;
            pt.attach(&allAddress[m+n]);
            pt.attach(&allAddress[m+1+n]);
        } else {
            if (k <=17) {
                int m =6;
                int n =(k-12);
                pt.attach(&allAddress[m+n]);
                pt.attach(&allAddress[m+n+6]);
            } else if ( k <= 25) {
                int m=12;
                int n = k-20;
                pt.attach(&allAddress[m+n]);
                pt.attach(&allAddress[m+n+6]);
            } else if ( k <=34) {
                int m = 18;
                int n = k-29;
                pt.attach(&allAddress[m+n]);
                pt.attach(&allAddress[m+n+6]);
            } else if (k <=42) {
                int m =24;
                int n = k- 37;
                pt.attach(&allAddress[m+n]);
                pt.attach(&allAddress[m+n+6]);
            } else if (k<=51) {
                int m=30;
                int n = k-46;
                pt.attach(&allAddress[m+n]);
                pt.attach(&allAddress[m+n+6]);
            } else {
                int m = 36;
                int n = k-54;
                pt.attach(&allAddress[m+n]);
                pt.attach(&allAddress[m+n+6]);
            }
        }
        pt.attach(gd);
        allPath.emplace_back(pt);
    }
    //vector<Address> allAddress;
    for (int k =0; k< 54; ++k){
        for (int t=0; t<72; ++t) {
            if (allPath[t].myNeighbourpos(k)) {
               // if (t==0) cout <<allPath[t].myNeighbourpos(k);
                allAddress[k].attach(&allPath[t]);
            }
        }
        allAddress[k].attach(gd);
        
    }
    /*for (int k=0; k<54; ++k) {
        if (k==0) {
            allAddress[k].setNeigh(&allAddress[1]);
            allAddress[k].setNeigh(&allAddress[3]);
        } else if ( k==1) {
            allAddress[k].setNeigh(&allAddress[0]);
            allAddress[k].setNeigh(&allAddress[4]);
        } else if ( k==3||k==2||k==4||k==5) {
            if (k==3){
                allAddress[k].setNeigh(&allAddress[0]);
            } else if (k==4) {
                allAddress[k].setNeigh(&allAddress[1]);
            }
            if (k%2==0) {
                allAddress[k].setNeigh(&allAddress[k+1]);
            } else {
                allAddress[k].setNeigh(&allAddress[k-1]);
            }
            allAddress[k].setNeigh(&allAddress[k+5]);
        } else if (k==52) {
            allAddress[k].setNeigh(&allAddress[49]);
            allAddress[k].setNeigh(&allAddress[53]);
        } else if (k==53) {
            allAddress[k].setNeigh(&allAddress[52]);
            allAddress[k].setNeigh(&allAddress[50]);
        } else if (k>=48&&k<=51) {
            if (k==49) {
                allAddress[k].setNeigh(&allAddress[52]);
            } else if (k==50) {
                allAddress[k].setNeigh(&allAddress[53]);
            }
            if (k%2==0) {
                allAddress[k].setNeigh(&allAddress[k+1]);
            } else {
                allAddress[k].setNeigh(&allAddress[k-1]);
            }
        } else if(k>=42 && k<=47){
            if (k>=43 && k<=46) {
                allAddress[k].setNeigh(&allAddress[k+5]);
                allAddress[k].setNeigh(&allAddress[k-6]);
            } else {
                allAddress[k].setNeigh(&allAddress[k+5]);
            }
            if (k%2==0) {
                allAddress[k].setNeigh(&allAddress[k+1]);
            } else {
                allAddress[k].setNeigh(&allAddress[k-1]);
            }

            
        } else if (k>=6 && k<=11) {
            if (k>=7 && k<=10) {
                allAddress[k].setNeigh(&allAddress[k-5]);
                allAddress[k].setNeigh(&allAddress[k+6]);
            } else {
                allAddress[k].setNeigh(&allAddress[k+6]);
            }
            if (k%2==0) {
                allAddress[k].setNeigh(&allAddress[k+1]);
            } else {
                allAddress[k].setNeigh(&allAddress[k-1]);
            }
            
            
            
        } else if (k%12<=5 && k<=36) {
            if (k%12 ==0 || k%12 == 5) {
                allAddress[k].setNeigh(&allAddress[k-6]);
                allAddress[k].setNeigh(&allAddress[k+6]);
            } else if (k%2==0) {
                allAddress[k].setNeigh(&allAddress[k-1]);
                allAddress[k].setNeigh(&allAddress[k-6]);
                allAddress[k].setNeigh(&allAddress[k+6]);
            } else {
                allAddress[k].setNeigh(&allAddress[k+1]);
                allAddress[k].setNeigh(&allAddress[k-6]);
                allAddress[k].setNeigh(&allAddress[k+6]);
            }
        } else {
            if (k%2==0) {
                allAddress[k].setNeigh(&allAddress[k+1]);
            } else {
                allAddress[k].setNeigh(&allAddress[k-1]);
            }
            allAddress[k].setNeigh(&allAddress[k-6]);
            allAddress[k].setNeigh(&allAddress[k+6]);
        }
    
    }*/
    setTile();
}


Board::~Board() {
    delete gd;
    delete [] aa;

}

void Board::setSeed(int k) {
    seed = k;
}

void Board::clean() {
   
    if (aa!=nullptr ){
    delete aa;
    aa = nullptr;
    }
    if (gd!= nullptr) {
    delete gd;
    gd=nullptr;
    }
}

int* Board::generateRan() {
    int index,tmp,i;
    int pos1=0;
    int pos2=0;
    int a[19]= {2,3,3,4,4,5,5,6,6,7,8,8,9,9,10,10,11,11,12};
    int b[19]= {0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,4,4,4,5};
    for(i=0;i<19;i++){
        index=rand()%18;
        if(index!=i){
            tmp=a[i];
            a[i]=a[index];
            a[index]=tmp;
        }
        if(a[index]==7){
            pos1=index;
        }
    }
    for(i=0;i<19;i++){
        index=rand()%19;
        if(index!=i){
            tmp=b[i];
            b[i]=b[index];
            b[index]=tmp;
        }
        if (b[index]==5){
            pos2=index;
        }
    }
    tmp=a[pos2];
    a[pos2]=7;
    a[pos1]=tmp;
   
    int *n = new int[38];
    int k = 0;
    for(i=0;i<19;i++){
        n[k] = b[i];
        //cout << n[k] << " " ;
        k++;
        n[k] = a[i];
        //cout << n[k] << " " ;
        k++;
    }
    /*cout <<endl;
    for (int k=0; k<38; ++k) {
        cout <<n[k] << " " ;
    }
    //cout <<endl;*/
    
    return n;
}


void Board::save(string file) {
    ofstream myfile;
    myfile.open(file);
    myfile << whoseTurn <<endl;
    for (auto &it : builderList) {
        myfile << it.save() <<endl;
    }
    for (int k=0; k< 38; ++k) {
        myfile <<aa[k] << " ";
    }
    myfile << aa[38] << endl;
}

int Board::myDice() {
    return dice;
}

void Board::setNewG(){
    gd->initialBoard(aa);
    setTileResource(aa);

}
void Board::setBug(int k) {
    builderList[whoseTurn].addSource(k, "Brick");
    builderList[whoseTurn].addSource(k, "Energy");
    builderList[whoseTurn].addSource(k, "Glass");
    builderList[whoseTurn].addSource(k, "Heat");
    builderList[whoseTurn].addSource(k, "Wifi");
}

void Board::load(string file) {
    ifstream f(file);
    string line;
    string s;
    int h;
    f >> whoseTurn;
    for (int k =0; k < 4; ++ k) {
        getline(f, line);
                builderList[k].loadInfo(line);
        stringstream ss{line};
        for(int m=0; m<5; ++m) {
            ss >>s;
        }
        while (ss >> s) {
            if (s=="r") {
                while (ss >> h) {
                    allPath[h].initRoad(&builderList[whoseTurn]);
                }
            } else if  (s == "h") {
                while (ss >> h) {
                    ss >> s;
                    allAddress[h].initBuild(&builderList[whoseTurn], s);
                }
            }
        }
    }
    //int a[38];
    int *a = new int[38];
    for (int k =0; k< 38; ++k) {
        f >> a[k];
    }
    delete [] aa;
    aa = nullptr ;
    aa =a;
    gd->initialBoard(a);
    setTileResource(a);
}

void Board::loadBoard(string file) {
    ifstream f (file);
    //int a[38];
    int *a = new int[38];
    for (int k =0; k< 38; ++k) {
        f >> a[k];
    }
    delete [] aa;
    aa = nullptr ;
    aa =a;
    gd->initialBoard(a);
    setTileResource(a);
}


void Board::setTile() {
    //vector<Tile> allTile;
    for (int k=0; k< 19; ++k){
        Tile t;
        t.setPos(k);
        
        if(k==0) {
            t.attach(&allAddress[0]);
            t.attach(&allAddress[1]);
            t.attach(&allAddress[3]);
            t.attach(&allAddress[4]);
            t.attach(&allAddress[8]);
            t.attach(&allAddress[9]);
            t.attach(&allPath[0]);
            t.attach(&allPath[1]);
            t.attach(&allPath[2]);
            t.attach(&allPath[6]);
            t.attach(&allPath[7]);
            t.attach(&allPath[10]);
        } else if (k== 18) {
            t.attach(&allAddress[44]);
            t.attach(&allAddress[45]);
            t.attach(&allAddress[49]);
            t.attach(&allAddress[50]);
            t.attach(&allAddress[52]);
            t.attach(&allAddress[53]);
            t.attach(&allPath[61]);
            t.attach(&allPath[64]);
            t.attach(&allPath[65]);
            t.attach(&allPath[69]);
            t.attach(&allPath[70]);
            t.attach(&allPath[71]);
            
        } else if (k==2 || k==1) {
            int m = 2*k;
            t.attach(&allAddress[m]);
            t.attach(&allAddress[m+1]);
            t.attach(&allAddress[m+5]);
            t.attach(&allAddress[m+6]);
            t.attach(&allAddress[m+11]);
            t.attach(&allAddress[m+12]);
            int n = k+2;
            t.attach(&allPath[n]);
            t.attach(&allPath[n+k+1]);
            t.attach(&allPath[n+k+2]);
            t.attach(&allPath[n+k+9]);
            t.attach(&allPath[n+k+10]);
            t.attach(&allPath[n+15]);
        } else if (k == 16 ||k ==17) {
            int m = 2*k+5;
            t.attach(&allAddress[m]);
            t.attach(&allAddress[m+1]);
            t.attach(&allAddress[m+6]);
            t.attach(&allAddress[m+7]);
            t.attach(&allAddress[m+11]);
            t.attach(&allAddress[m+12]);
            int n = k+36;
            t.attach(&allPath[n]);
            t.attach(&allPath[n+k-13]);
            t.attach(&allPath[n+k-12]);
            t.attach(&allPath[n+k-5]);
            t.attach(&allPath[n+k-4]);
            t.attach(&allPath[n+15]);
        } else {
            int j=0;
            if (k <= 5) {
                j = 0;
            } else if (k <= 7) {
                j= 1;
            } else if ( k <= 10) {
                j= 2;
            } else if ( k <= 12) {
                j= 3;
            } else if ( k <= 15) {
                j =4;
            }
            int m = 2*k + j;
            t.attach(&allAddress[m]);
            for (int g=0; g<5; ++g) {
                if (g%2==0) {
                    m+=1;
                } else {
                    m+=5;
                }
                t.attach(&allAddress[m]);
            }
            int p=0;
            int h=0;
            int q=0;
            if (k <= 5) {
                p = 6;
                h= k;
            } else if (k <= 7) {
                p=12;
                h=k-3;
                q=1;
            } else if ( k <= 10) {
                p= 18;
                h=k-5;
            } else if ( k <= 12) {
                p= 24;
                h=k-8;
                q=1;
            } else if ( k <= 15) {
                p =30;
                h=k-10;
            }
            int n = k+p;
            t.attach(&allPath[n]);
            t.attach(&allPath[n+h]);
            t.attach(&allPath[n+h+1]);
            t.attach(&allPath[n+h+8+q]);
            t.attach(&allPath[n+h+9+q]);
            t.attach(&allPath[n+17]);
        }
        allTile.emplace_back(t);
    }
}

void Board::setTileResource(int *a) {
    int l=0;
    for (int k =0; k<19; ++k) {
        allTile[k].setSour(a[l]);
        l+=1;
        allTile[k].setDice(a[l]);
        l+=1;
    }
}

void Board::Diceload(int k) {
    dice=k;
}

void Board::Dicefair() {
    int a = rand() % 6+1;
    int b = rand() % 6+1;
    dice = a+b;
}
void Board::nextTurn() {
    if (whoseTurn == 3) {
        whoseTurn =0;
    } else {
        whoseTurn +=1;
    }
}

string Board::who () {
    if (whoseTurn == 0) {
        return "Blue";
    } else if (whoseTurn ==1){
        return "Red";
    } else if (whoseTurn == 2) {
        return "Orange";
    } else {
        return "Yellow";
    }
}

void Board::setTurn(int t ) {
    whoseTurn = t;
}

bool Board::setInitHouse(int where) {
    string colour =builderList[whoseTurn].myColour();
    if (where >=0 && where<=53) {
        if (allAddress[where].belongTo() == "noOne" && allAddress[where].canIBuild(colour,1) ){
            allAddress[where].initBuild(&builderList[whoseTurn], "B");
            for (auto &it : allTile) {
                if( it.isIn(where)){
                    //cout << "100" <<endl;
                    it.setBuilder(&builderList[whoseTurn]);
                }
            }
            return true;

        } else {
            cout << "You cannot build here. Try again!" <<endl;
            return false;
        }
    } else {
        cout << "You cannot build here. Try again!" <<endl;
        return false;
    }
}

bool Board::isWon() {
    for (int k=0; k<4; ++k){
        if (builderList[k].myScore()==10) {
            return true;
        }
    }
    return false;
}

string Board::whoWon() {
    for (int k=0; k< 4; ++k){
        if (builderList[k].myScore() ==10) {
            return builderList[k].myColour();
        }
    }
    return "noone";
}

void Board::printStatus() {
    for (int k=0; k< 4; ++k){
        builderList[k].status();
    }
    //gd->print();//not yet
}


void Board::printRes() {
    builderList[whoseTurn].printRes();
}

void Board::gainResource() {
    for (auto &it: allTile) {
        if (it.myDice()== dice  ){
            it.whoGainWhat();
        }
    }
}



void Board::buildRoad(int path) {
    string colour =builderList[whoseTurn].myColour();
    if (builderList[whoseTurn].canIBuildIt("P") && allPath[path].canIBuild(colour,0)&& allPath[path].belongTo() == "noOne"  ) {
        allPath[path].buildRoad(&builderList[whoseTurn]);
    } else if (builderList[whoseTurn].canIBuildIt("P")){
        cout << "You cannot build here." <<endl;
    } else {
        cout << "You do not have enough resource."<<endl;
    }
    //} else {
    //     cout << "You do not have enough resources" <<endl;
    // }
}


void Board::buildRes(int address) {
    string colour =builderList[whoseTurn].myColour();
    if (builderList[whoseTurn].canIBuildIt("B")  && allAddress[address].canIBuild(colour,0) && allAddress[address].belongTo() == "noOne") {
        allAddress[address].buildRes(&builderList[whoseTurn]);
        for (auto &it : allTile) {
            if( it.isIn(address)){
                //cout << "1" <<endl;
                it.setBuilder(&builderList[whoseTurn]);
            }
        }
    } else if (! (allAddress[address].canIBuild(colour,0) && allAddress[address].belongTo() == "noOne")) {
        //cout <<(allAddress[address].canIBuild(colour,0))<<endl;
        //cout <<allAddress[address].belongTo()<<endl;
        cout <<"You cannot build here."<<endl;
    } else if (!builderList[whoseTurn].canIBuildIt("B")){
        cout << "You do not have enough resource."<<endl;
    } else {
        cout <<"other"<<endl;
    }
}
    //} else {
    //     cout << "You do not have enough resources" <<endl;
    // }
void Board::improve(int address) {
    string Type = builderList[whoseTurn].whatOnThere(address);
    string colour =builderList[whoseTurn].myColour();
    if (builderList[whoseTurn].canIBuildIt(Type) ) {
        allAddress[address].improve();
    } else  if  (!builderList[whoseTurn].canIBuildIt(Type)) {
        cout <<"You do not have enough resource."<<endl;
    
    }
}

void Board::geese() {
    for (int k =0; k < 4; ++k) {
        builderList[k].geese();
    }
}

bool Board::someoneOnTile(int pos) {
    return allTile[pos].SomeoneOnTile();
}

void Board::moveGeese(int posNum) {
    if (someoneOnTile(posNum)){
        cout << "Builder " << builderList[whoseTurn].myColour() << " can choose to steal from: "<<endl;
        allTile[posNum].whoOnTile(builderList[whoseTurn].myColour());
        cout << endl;
    }
    gd->geesePos(posNum);
}

void Board::steal(string w) {
    string s;
    int c =builderColour[w];
    s = builderList[c].stealSource();
    builderList[whoseTurn].addSource(1, s);
    builderList[builderColour[w]].removeSource(s);
    cout << "Builder " <<builderList[whoseTurn].myColour()<< " steal " << s << " from builder " << w << "."<<endl;
}

void Board::trade(string build, string source1, string source2) {
    int k= builderColour[build];
    //cout << builderColour[build] <<endl;
    builderList[whoseTurn].trade(&builderList[k], source1, source2);
}
ostream &operator<<(ostream &out, const Board &b) {
    out << *b.gd;
    return out;
}

void Board::bug2() {
    builderList[whoseTurn].bug2();
}
