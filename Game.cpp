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
    
    void printSummary(){
        cout << "Player Win | Player Loss | Tie\n" <<
        playerWin << " | " << playerLoss << " | " << ties << "\n\n\n";
    }
    
    char convertToUpper(char c){
        if(c >= 97){
            c -= 32;
        }
        return c;
    }
    
    
public:
    Game(){
        cout << "Please indicate which type of AI you want to play against.\n";
        cout << "Warning: Currently, only markov-chain agent is available.\n";
        cout << "Type Q to quit\n\n";
        
    }
    

    
    void playRound(){
        int agentChoice = agent.predict();
        cout << "Please type your choice(R/P/S).\n";
        char userInput;
        int userChoice = -1;
        while(userChoice == -1){
            cin >> userInput;
            userInput = convertToUpper(userInput);
            if(userInput == 'R'){
                userChoice = 0;
            }
            else if(userInput == 'P'){
                userChoice = 1;
            }
            else if(userInput == 'S'){
                userChoice = 2;
            }
            else if(userInput == 'Q'){
                exit(0);
            }
            else{
                cout << "Illegal Input\n";
            }
        }
        
        // Illegal Input
        
        
        
        cout << "Agent played " << MAP[agentChoice] << '\n';
        
        if(RESULT[userChoice][agentChoice] == 0) ties++;
        else if(RESULT[userChoice][agentChoice] == 1) playerWin++;
        else playerLoss++;
        
        printSummary();
        
        agent.learn(userChoice);
    }
    
    
};
