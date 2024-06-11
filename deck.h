#ifndef DECK
#define DECK

#include <iostream>
#include "card.h"

class Deck {
public:
    Deck();
    void shuffle();
    
    // used to deal cards
    Card dealTopCard();


private:
    Card cards_[52];
    int top_;
};


#endif