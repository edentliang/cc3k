#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "board.h"
#include <algorithm>
using namespace std;

int main (int argc, char *argv[]) {
    int seed =0;
    string gameState= "random";
    string boardState;
    string loadfile, boardfile;
    for (int k =1; k < argc; ++k){
        if ( string(argv[k]) =="seed" ) {
            stringstream ss(argv[k+1]);
            ss >> seed;
            srand(seed);
        } else if (string(argv[k]) == "load") {
            loadfile = string (argv[k+1]);
            gameState = "load";
        } else if (string (argv[k]) == "board") {
            boardfile =string (argv[k+1]);
            boardState = "board";
        } else if (string (argv[k]) == "random-board") {
            boardState = "random";
        }
    }
    
    cin.exceptions (ios::eofbit | ios::failbit);

    vector<string> v;
    v.emplace_back("Blue");
    v.emplace_back("Red");
    v.emplace_back("Orange");
    v.emplace_back("Yellow");
    v.emplace_back("Brick");
    v.emplace_back("Energy");
    v.emplace_back("Glass");
    v.emplace_back("Heat");
    v.emplace_back("Wifi");
    int pos;
    int diceNum;
    string com;
    string colour;
    string source1, source2;
    
    
    while (true) {
        Board b;
        b.initBoard();
        
        if (boardState == "board") {
            b.loadBoard(boardfile);
        } else {
            b.setNewG();
        }
        if ( gameState != "load") {
            cout << b;
            while (true) {
                while (true) {
            cout << "Builder " << b.who() << ", where do you want to build a basement?" <<endl;
                cout << ">";
                string ttt;
                int ppp;
                cin >> ttt;
                stringstream ss{ttt};
                ss >>ppp;
                    if (b.setInitHouse(ppp)){
                        b.nextTurn();
                        break;
                    }
                }
                if (b.who() == "Blue") break;
            }
            
            int Turn =3;
            while (true) {
                b.setTurn(Turn);
                while (true) {
                cout << "Builder " << b.who()<< ", where do you want to build a basement?" <<endl;
                string ttt;
                int ppp;
                cout << ">";
                cin >> ttt;
                stringstream ss{ttt};
                ss >>ppp;
                    if (b.setInitHouse(ppp)) {
                        Turn -=1;
                        break;
                    }
                }
                if (Turn  == -1) {
                    break;
                }
            }
            b.setTurn(0);
        } else {
            b.load (loadfile);
        }
        
        b.setSeed(seed);
        
    while (true) {
            if (b.isWon()) {
                break;
            }
            cout << "Builder " << b.who()<<"'s turn." << endl;
            while (true) {
                string tt;
                //1cout << "Choose dice type(fair or load)"<<endl;
                cout << ">";
                cin >> com;
                if (com  == "load") {
                 while (true){
                    cout << "Input a roll between 2 and 12:" <<endl;
                    cout << ">";
                    cin >> tt;
                    stringstream ss{tt};
                    
                    if (ss>>diceNum && diceNum >= 2 && diceNum <=12) {
                        b.Diceload(diceNum);
                        cout << "Please roll."<<endl;
                        break;
                    } else {
                        cout << "Invalid roll." <<endl;
                        cin.clear();
                        cin.ignore();
                    }
                    }
                } else if (com == "fair") {
                    b.Dicefair();
                    cout << "Please roll."<<endl;
                    
                } else if (com == "roll") {
                    cout << "Result is " << b.myDice() <<endl;
                    if (b.myDice() ==7){
                        int pp;
                        b.geese();
                        cout << "Choose where to place the GEESE." <<endl;
                        while (true) {
                        cin >> tt;
                        stringstream ss{tt};
                            if (ss>> pp && pp>=0 && pp<= 18) {
                            if (b.someoneOnTile(pp)){
                            b.moveGeese(pp);
                            cout << "Choose a builder to steal from."<<endl;
                            cin >> tt;
                            b.steal(tt);
                            break;
                            } else{
                                cout << "Builder "<< b.who() << " has no builders to steal from."<<endl;
                                b.moveGeese(pp);
                                break;
                            }
                        } else  if (!ss>>pp || pp<0 ||pp>18) {
                            cout << "Invalid input"<<endl;
                        }
                        }
                        
                        
                    } else {
                        b.gainResource();
                    }
                    
                    while (true) {
                        cout <<"Command?"<<endl;
                        cout << ">";
                        cin >> com;
                        if (com == "board") {
                            cout << b;
                        } else if ( com == "status") {
                            b.printStatus();
                        } else if ( com == "residence") {
                            b.printRes();
                        } else if (com == "build-road") {
                            cout << "Where do you want to build?"<<endl;
                            cout << ">";
                            cin >> com;
                            stringstream ss{com};
                            if (ss >> pos) {
                                b.buildRoad(pos);
                            } else {
                                cout << "Invalid input"<<endl;
                            }
                        } else if ( com == "build-res") {
                            cout << "Where do you want to build?"<<endl;
                            cout << ">";
                            cin >> com;
                            stringstream ss{com};
                            if (ss >> pos) {
                                b.buildRes(pos);
                            } else {
                                cout << "Invalid input"<<endl;
                            }
                        } else if (com == "improve") {
                            cout << "Where do you want to build?"<<endl;
                            cout << ">";
                            cin >> com;
                            stringstream ss{com};
                            if (ss >> pos) {
                                b.improve(pos);
                            } else {
                                cout << "Invalid input"<<endl;
                            }
                        } else if (com =="trade") {
                            while (true) {
                            cout << ">";
                            cin >> colour >>source1 >>source2;
                        if (find(v.begin(), v.end(), colour) != v.end()&&
                            find(v.begin(), v.end(), source1) != v.end() &&
                            find(v.begin(), v.end(), source2) != v.end()){
                            cout << b.who()<< " offers "<< colour << " one ";
                            cout << source1 <<" for one "<<source2 << "."<<endl;
                            cout <<"Does "<< colour << " accept this offer?"<<endl;
                            cout << ">";
                            cin >> com;
                            if ( com == "yes") {
                                b.trade(colour, source1, source2);
                            }
                            break;
                        }
                            }
                        } else if (com =="next") {
                            break;
                        } else if (com == "save") {
                            string file;
                            cout << ">";
                            cin >> file;
                            b.save(file);
                        } else if ( com == "help"){
                            cout << "Valid commands:" <<endl;
                            cout << "board"<<endl;
                            cout << "status"<<endl;
                            cout <<"residence" <<endl;
                            cout <<"build-road <path#>" <<endl;
                            cout <<"build-res <housing#>" <<endl;
                            cout <<"improve <housing#>" <<endl;
                            cout <<"trade <colour> <give> <take>" <<endl;
                            cout <<"next" <<endl;
                            cout <<"save <file>" <<endl;
                            cout<<"help" <<endl;
                        } else if (com =="bug"){
                            b.setBug(10);
                        } else if (com =="bug2") {
                            b.bug2();
                        } else {
                            cout <<"Invalid input2" <<endl;
                        }
                    }
                    b.nextTurn();
                    break;
                } else {
                    cout <<"Invalid input1" <<endl;
                }
            }//one turn  done
    }//game done
        if (b.isWon()) {
            cout << b.whoWon() << " won!"<<endl;
        }
        cout << "Would you like to play again?"<<endl;
        cout << ">";
        cin >> com;
        if (com == "no") {
            break;
        } else {
            gameState = "random";
        }
    }
}
//2017.12.00003

