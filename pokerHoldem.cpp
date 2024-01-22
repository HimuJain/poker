#include <iostream>
#include <cstdlib>
#include <unistd.h>
using namespace std;

void shuffleCards(int deck[]);
int deal(int deck[], int playHands[][5], int numPlay, int deckTop, int round);
int communityDeal(int deck[], int communityCards[], int deckTop, int round);

// ♥, ♠, ♦, ♣; each suit as a unicode character
const char *suit[4] = {"\U00002665", "\U00002660", "\U00002666", "\U00002663"};
// the card type for each card
const char *type[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};


// literally just shuffling cards
void shuffleCards(int deck[])
{
    // using a shuffle algorithm
    for (int i = 52 - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int swap = deck[i];
        deck[i] = deck[j];
        deck[j] = swap;
    }
}

// dealing for players
int deal(int deck[], int playHands[][5], int numPlay, int deckTop, int round)
{
    // decrement round to use for array indicies
    round--;
    for (int i = 0; i < numPlay; i++)
    {
        // assign the present top of the deck to player #i's hand (depending on which round it is)
        playHands[i][round] = deck[deckTop];
        deckTop++;
    }
    return deckTop;
}

// dealing for community cards
int communityDeal(int deck[], int communityCards[], int deckTop, int round)
{
    round--;
    communityCards[round] = deck[deckTop];
    return deckTop + 1;
}

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
    cout << "How many players would you like? (2-4)" << endl; // not including player
    int numPlay;
    cin >> numPlay;
    while (numPlay < 2 || numPlay > 4)
    {
        cout << "Please enter a number between 2 and 4." << endl;
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
        // initialize reset player hands
        int playHands[5][5];
        for (int i = 0; i < numPlay; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                playHands[i][j] = 0;
            }
        }

        // shuffle deck
        int cardDeck[52];
        for (int i = 0; i < 52; i++)
        {
            cardDeck[i] = i;
        }

        // TODO: add seed later for random number generator
        cout << "Shuffling cards..." << endl;
        shuffleCards(cardDeck);
        sleep(3);

        // TODO: add dice roll/random number later to change order
        // for now, player order remains at 0 (i.e. 0th index of array)
        int playerIndex = 0;

        // dealing cards
        cout << "Dealing cards..." << endl;
        int deckTop = 0;

        // run twice for 2 cards in each hand
        deckTop = deal(cardDeck, playHands, numPlay, deckTop, 1);
        deckTop = deal(cardDeck, playHands, numPlay, deckTop, 2);
        sleep(3);

        // big and small bets
        int pot = 0;
        cout << "'Dealer' is Player #" << dealerIndex << ", so Players " << dealerIndex + 1 << " and " << dealerIndex + 2 << "  please bet $5 and $10, respectively." << endl;
        balances[dealerIndex + 1] -= 5;
        balances[dealerIndex + 2] -= 10;
        pot += 15;

        // initalize community card array
        int comCards[5];
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

        break;
    }

    return 0;
}
