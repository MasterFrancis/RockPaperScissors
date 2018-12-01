//
//  MarkovAgent.cpp
//  RPS
//
//  Created by Francis Zhang on 11/30/18.
//  Copyright © 2018 Yiming Zhang. All rights reserved.
//
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
using namespace std;
int Rock = 0;
int Paper = 1;
int Scissors = 2;
// Maps ints to according names
string MAP[] = {"Rock", "Paper", "Scissors"};

// Maps prediction of user play to according winning play
int winning[] = {1, 2, 0};

// 0 for tie, 1 for playerWin, 2 for playerLoss
// First Dimension is User Input, Second Dimension is AI Input
int RESULT[3][3] = {{0, 2, 1}, {1, 0, 2}, {2, 1, 0}};

// Markov Chain with length 3
class MarkovAgent{
private:
    double Count[3][3][3] = {{{0,0,0},{0,0,0},{0,0,0}}
        ,{{0,0,0},{0,0,0},{0,0,0}}
        ,{{0,0,0},{0,0,0},{0,0,0}}};
    int last2 = -1;
    int last1 = -1;
    
    // Store Count to a text file
    void write(){
        
        ofstream OFS;
        OFS.open("count.txt");
        
        for(int i = 0; i < 3; ++i){
            for(int j = 0; j < 3; ++j){
                for(int k = 0; k < 3; ++k){
                    OFS << Count[i][j][k] << '\n';
                }
            }
        }
    }

    void read(){
        ifstream IFS;
        IFS.open("count.txt");
        if(IFS.is_open()){
            for(int i = 0; i < 3; ++i){
                for(int j = 0; j < 3; ++j){
                    for(int k = 0; k < 3; ++k){
                        IFS >> Count[i][j][k];
                    }
                }
            }
        }
    }
public:
    MarkovAgent(){
        srand(time(0));
        read();
    }
    int predict(){
        if(last1 == -1 || last2 == -1){
            return rand() % 3;
        }
        else{
            vector<int> maxIndex = {0};
            if(Count[last2][last1][1] > Count[last2][last1][maxIndex[0]]){
                maxIndex.clear();
                maxIndex.push_back(1);
            }
            if(Count[last2][last1][1] == Count[last2][last1][maxIndex[0]]){
                maxIndex.push_back(1);
            }
            if(Count[last2][last1][2] > Count[last2][last1][maxIndex[0]]){
                maxIndex.clear();
                maxIndex.push_back(2);
            }
            if(Count[last2][last1][2] == Count[last2][last1][maxIndex[0]]){
                maxIndex.push_back(2);
            }
            
            return winning[maxIndex[rand() % maxIndex.size()]];
        }
    }
    void learn(int current){
        if(last1 == -1 || last2 == -1){
            last2 = last1;
            last1 = current;
        }
        else{
            Count[last2][last1][current]++;
            last2 = last1;
            last1 = current;
            
        }
        write();
    }
    
};
