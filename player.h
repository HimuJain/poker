#include <iostream>
#include <vector>
#include <string>
#include "card.h"

// *this is a POKER specific class for now, so it deals with the concept of ranking different hands

// create hand class AND player class?
// ? how many classes should you use in one program?
class Player{
public:
    // ? pass in optional arguments for AI?
    Player();
    Player(int numCards);

    // hand functions

    // ? if there is a valid hand, then the cards are highlighted; will the comCards print too?
    void printHand();
    // todo: should have a return value so we can compare against other players
    void findBestHand(Player comCards);
    void addCard(Card dealt);
    // reset the player's hand, their bet and whether they folded or not 
    void resetPlayer();

    // money functions

    bool checkOrFold(int betAmount, int* pot);


private:
    // acts as an id for the player
    int idNum_;

    std::string name_;

    std::vector<Card> hand_;
    // rank the hands in order of superiority
    int handRank_;
    // amount of money player has
    int balance_;
    // amount they bet
    int bet_;
    // whether they fold
    bool folded_;
    // whether they are an ai
    bool ai_;
    // ? inheritence for AI class?
};