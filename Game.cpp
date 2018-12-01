#include <string>
#include <iostream>
#include "MarkovAgent.cpp"
using namespace std;


class Game{
private:
    int playerLoss = 0;
    int playerWin = 0;
    int ties = 0;
    MarkovAgent agent;
    
    
public:
    Game(){
        cout << "Please indicate which type of AI you want to play against.\n";
        cout << "Warning: Currently, only markov-chain agent is available.\n";
        
    }
    
    void printSummary(){
        cout << "Player Win | Player Loss | Tie\n" <<
        playerWin << " | " << playerLoss << " | " << ties << "\n\n\n";
    }
    
    void playRound(){
        int agentChoice = agent.predict();
        cout << "Please type your choice(R/P/S).\n";
        char userInput;
        cin >> userInput;
        int userChoice = -1;
        if(userInput == 'R'){
            userChoice = 0;
        }
        else if(userInput == 'P'){
            userChoice = 1;
        }
        else if(userInput == 'S'){
            userChoice = 2;
        }
        // Illegal Input
        
        else{
            cout << "Illegal Input\n";
            exit(1);
        }
        
        cout << "Agent played " << MAP[agentChoice] << '\n';
        
        if(RESULT[userChoice][agentChoice] == 0) ties++;
        else if(RESULT[userChoice][agentChoice] == 1) playerWin++;
        else playerLoss++;
        
        printSummary();
        
        agent.learn(userChoice);
    }
    
    
};
