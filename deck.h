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

Deck::Deck() {
    for (int i = 0; i < 52; i++) {
        Card temp(i);
        cards_[i] = temp;
    }
    top_ = 0;
}

void Deck::shuffle() {
    // may implement a rand function of some sort to allow for the same seed to result in the same game across different OSes.
    for (int i = 52 - 1; i >= 0; i--) {
        int j = rand() % (i + 1);
        Card swap = cards_[i];
        cards_[i] = cards_[j];
        cards_[j] = swap;
    }
}

// used for drawing cards from the deck
Card Deck::topCard_get() {
    return cards_[top_++];
}