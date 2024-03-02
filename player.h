#include <iostream>
#include "card.h"

// *this is a POKER specific class for now, so it deals with the concept of ranking different hands

class Player{
public:
    Player();
    Player(int numCards);
    void printHand();
    void findBestHand(Player comCards);
    // reset the player's hand, their bet and whether they folded or not 
    void resetPlayer();
    void addCard(Card dealt);

private:
    // acts as an id for the player
    int num_;

    vector<Card> hand_;
    // rank the hands in order of superiority
    int handRank_;
    // amount of money player has
    int balance_;
    // amount they bet
    int bet_;
    // whether they fold
    bool folded_;
    bool ai_;
    // ? inheritence for AI class?
};