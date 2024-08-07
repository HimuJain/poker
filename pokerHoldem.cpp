#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "card.h"
#include "player.h"
#include "deck.h"
using namespace std;


int main()
{
    // welcome messages
    cout << "Welcome to Poker!" << endl;
    cout << "How many players would you like? (2-10)" << endl; // not including player
    int numPlay;
    cin >> numPlay;
    while (numPlay < 2 || numPlay > 10)
    {
        cout << "Please enter a number between 2 and 10." << endl;
        cin >> numPlay;
    }
    cout << "What is the default balance you would like each player to start with?" << endl;
    int balance;
    cin >> balance;
    // * note: must change to polymorphism to allow for ai inherited class
    vector<Player> allPlayers;
    for(int i = 1; i <= numPlay; i++){
        cout << "What is Player " << i << "'s name ?" << endl;
        string name;
        cin >> name;
        allPlayers.push_back(Player(i, name, balance));
    }
    int playerIndex = -1;
    // cout << "Which Player are you? (1 - " << numPlay << ")" << endl;
    // cin >> playerIndex;
    // while(playerIndex < 1 || playerIndex > numPlay){
    //     cout << "Invalid Player ID inputted. Please input an ID between 1 and " << numPlay << "." << endl;
    // }
    


    // * game loop

    bool quit = false;
    // treated as an ID, and not the thing to be printed (so +1 every time when printing)
    int firstPlayer = 0;
    Deck pokerDeck;
    while (!quit)
    {
        // player index (will be randomized in the loop)
        firstPlayer %= numPlay;
        // record the present check value (minimum payment to keep playing)
        int check;
        // community cards
        Player comCards;

        // shuffle deck
        cout << "Shuffling cards.." << endl;
        pokerDeck.shuffle();

        // TODO: add seed later for random number generator

        // dealing cards
        cout << "Dealing cards..." << endl;
        for(int i = 0; i < numPlay; i++){
            allPlayers[i].addCard(pokerDeck.dealTopCard());
            allPlayers[i].addCard(pokerDeck.dealTopCard());
        }
        
        
        
        int pot = 0;
        check = 10; // as default check value for now, could implement changes later
        // big and small bets (should print the player number (1 - n) + however many required for the other players, so some weird math is required)
        // ! unsure if the math holds, debug later and check
        cout << "'Dealer' is Player #" << (firstPlayer % numPlay)+1 << ", so Players " << ((firstPlayer + 1) % numPlay) + 1 << " and " << ((firstPlayer + 2) % numPlay) + 1 << "  will bet $" << check/2 << " and $" << check << ", respectively. " << endl;
        for(int i = 1; i < 3; i++){
            allPlayers[((firstPlayer + i) % numPlay)].betMoney((check*i/2), &pot);
        }
        // logic to make sure all players have checked or folded
        int numDone = 0, i = ((firstPlayer + 2) % numPlay);
        while(numDone != numPlay){
            char ready = 'n';
            while(ready != 'y'){
                cout << "Please enter 'y' when Player " << i+1 << " is at the computer." << endl;
                cin >> ready;
            }   
            for(int j = 0; j < 7; j++){
                for(int k = 0; k < numPlay; k++){
                    allPlayers[k].printInfo(i+1, j, comCards);
                    cout << " ";
                }
                cout << endl;
            }
            if(allPlayers[i].checkBetOrFold(&check, &pot)){
                numDone++;
            }
            else{
                numDone = 0;
            }
            i++;
            i %= numPlay;
        }


        // deal community cards and print them
        // * first stage: flop (3 cards)
        for(int i = 0; i < 3; i++){
            comCards.addCard(pokerDeck.dealTopCard());
        }


        for(int i = 0; i < 5; i++){
            allPlayers[i].resetBet();
        }

        check = 0;
        numDone = 0;
        while(numDone != numPlay){
            for(int j = 0; j < 7; j++){
                for(int k = 0; k < numPlay; k++){
                    allPlayers[k].printInfo(i+1, j, comCards);
                    cout << " ";
                }
                cout << endl;
            }
            if(allPlayers[i].checkBetOrFold(&check, &pot)){
                numDone++;
            }
            else{
                numDone = 0;
            }
            i++;
            i %= numPlay;
        }

        // * second stage: turn (1 card)

        comCards.addCard(pokerDeck.dealTopCard());


        for(int i = 0; i < 5; i++){
            allPlayers[i].resetBet();
        }

        check = 0;
        numDone = 0;
        while(numDone != numPlay){
            for(int j = 0; j < 7; j++){
                for(int k = 0; k < numPlay; k++){
                    allPlayers[k].printInfo(i+1, j, comCards);
                    cout << " ";
                }
                cout << endl;
            }
            if(allPlayers[i].checkBetOrFold(&check, &pot)){
                numDone++;
            }
            else{
                numDone = 0;
            }
            i++;
            i %= numPlay;
        }
        
        // * last stage: river (1 card)


        comCards.addCard(pokerDeck.dealTopCard());


        for(int i = 0; i < 5; i++){
            allPlayers[i].resetBet();
        }

        check = 0;
        numDone = 0;
        while(numDone != numPlay){
            for(int j = 0; j < 7; j++){
                for(int k = 0; k < numPlay; k++){
                    allPlayers[k].printInfo(i+1, j, comCards);
                    cout << " ";
                }
                cout << endl;
            }
            if(allPlayers[i].checkBetOrFold(&check, &pot)){
                numDone++;
            }
            else{
                numDone = 0;
            }
            i++;
            i %= numPlay;
        }


        break;
    }

    return 0;
}
