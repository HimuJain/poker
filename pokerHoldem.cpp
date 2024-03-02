#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "card.h"
#include "player.h"
#include "deck.h"
using namespace std;


void deal(int numPlayers, int numCards);
// int deal(int deck[], int playHands[][2], int numPlay, int deckTop);
// int communityDeal(int deck[], int communityCards[], int deckTop, int round);

// ♥, ♠, ♦, ♣; each suit as a unicode character
const char* suit[4] = {"\U00002665", "\U00002660", "\U00002666", "\U00002663"};
// the card type for each card
const char* type[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};


// literally just shuffling cards
void shuffleCards(int deck[])
{
    // using a shuffle algorithm
    for (int i = 52 - 1; i >= 0; i--)
    {
        int j = rand() % (i + 1);
        int swap = deck[i];
        deck[i] = deck[j];
        deck[j] = swap;
    }
}

// dealing for players
int deal(int deck[], int playHands[][2], int numPlay, int deckTop)
{
    // decrement round to use for array indicies
    for (int i = 0; i < numPlay; i++)
    {
        // assign the present top 2 cards of the deck to player #i's hand
        playHands[i][0] = deck[deckTop];
        playHands[i][1] = deck[deckTop];
        deckTop += 2;
    }
    return deckTop;
}

// dealing for community cards
int communityDeal(int deck[], int communityCards[], int deckTop, int round)
{
    round--;
    communityCards[round] = deck[deckTop];
    return ++deckTop;
}

// prints out the cards in a hand
void printCards(int hand[], int round){
    round;
    for(int i = 0; i < round; i++){
        cout << type[hand[i] % 13] << suit[hand[i] / 13] << ' ';
    }
    cout << endl;
}




int main()
{
    // welcome messages
    cout << "Welcome to Poker!" << endl;
    cout << "How many players would you like? (2-5)" << endl; // not including player
    int numPlay;
    cin >> numPlay;
    while (numPlay < 2 || numPlay > 5)
    {
        cout << "Please enter a number between 2 and 5." << endl;
        cin >> numPlay;
    }

    numPlay++; //number of players including player

    // initalize player balances
    int balances[5];
    for (int i = 0; i < 5; i++)
    {
        balances[i] = 1000;
    }

    // initialize dealer index outside of the loop to increment
    int dealerIndex = 0;


    


    // * game loop

    bool quit = false;
    while (!quit)
    {
        // player index (will be randomized in the loop)
        int playerIndex;
        // record the top card index of the deck
        int deckTop;
        // record the pot of the cards
        int pot;
        // record the present check value (minimum payment to keep playing)
        int check;

        // community cards used for the faceup cards
        int comCards[5];
        // 2D array to record each player's hands
        int playHands[6][2];
        // full deck of cards
        int cardDeck[52];
        // records how much each player has bet so far (to ensure equal bets at the end)
        int bets[6];

        // initialize reset player hands
        for (int i = 0; i < numPlay; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                playHands[i][j] = 0;
            }
        }

        // shuffle deck
        for (int i = 0; i < 52; i++)
        {
            cardDeck[i] = i;
        }
        deckTop = 0;

        // TODO: add seed later for random number generator
        cout << "Shuffling cards..." << endl;
        shuffleCards(cardDeck);
        sleep(3);

        // TODO: add dice roll/random number later to change order
        // for now, player order remains at 0 (i.e. 0th index of array)
        playerIndex = 0;

        // dealing cards
        cout << "Dealing cards..." << endl;
        
        deckTop = deal(cardDeck, playHands, numPlay, deckTop);
        // run twice for 2 cards in each hand
        sleep(3);

        for(int i = 0; i < numPlay; i++){
            bets[i] = 0;
        }
        
        pot = 0;
        check = 10; // as default check value for now, could implement changes later
        // big and small bets
        cout << "'Dealer' is Player #" << dealerIndex << ", so Players " << dealerIndex + 1 << " and " << dealerIndex + 2 << "  please bet $" << check/2 << " and $" << check << ", respectively." << endl;
        balances[dealerIndex + 1] -= check/2.0;
        bets[dealerIndex + 1] += check/2.0;
        balances[dealerIndex + 2] -= check;
        bets[dealerIndex + 2] += check/2.0;
        pot += check * (3.0/2);

        // initalize community card array
        for (int i = 0; i < 5; i++)
        {
            comCards[i] = 0;
        }

        // deal community cards and print them
        deckTop = communityDeal(cardDeck, comCards, deckTop, 1);
        deckTop = communityDeal(cardDeck, comCards, deckTop, 2);
        deckTop = communityDeal(cardDeck, comCards, deckTop, 3);
        cout << "Community cards: ";
        printCards(comCards, 3);

        for(int i = 0; i < numPlay - 2; i++)
        {
            int playNum = (dealerIndex + 2 + i) % 5;
            char playerChoice;
            if(playNum == playerIndex){
                cout << "What would you like to do? Check, Raise, or Fold (c/r/f)." << endl;
                playerChoice = 'd';
                while(!(playerChoice == 'c' || playerChoice == 'r' || playerChoice == 'f')){
                    cin >> playerChoice;
                    if(playerChoice == 'c'){
                        balances[playerIndex] -= check;
                        pot += check;
                    }
                    else if(playerChoice == 'r'){
                        cout << "How much would you like to raise?" << endl;
                        int raise;
                        cin >> raise;
                        while(raise < check){
                            cout << "You cannot raise less than $" << check << ". Please input a new raise." << endl;
                            cin >> raise;
                        }
                    
                    }
                }
            }
            cout << "Player #";
        }

        break;
    }

    return 0;
}
