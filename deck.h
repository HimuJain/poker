#include <iostream>
#include "card.h"

class Deck {
public:
    Deck();
    void shuffle();
    Card topCard_get();

private:
    Card cards_[52];
    int top_;
};
