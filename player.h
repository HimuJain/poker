#ifndef PLAYER
#define PLAYER

#include <iostream>
#include <vector>
#include <string>
#include "card.h"

// *this is a POKER specific class for now, so it deals with the concept of ranking different hands

// create hand class AND player class?
// ? how many classes should you use in one program?
class Player{
public:
    Player();
    Player(int id, std::string name, int balance, bool AI = false);
    
    virtual ~Player();

    // hand functions

    // ? if there is a valid hand, then the cards are highlighted; will the comCards print too?
    void printHand();
    // todo: should have a return value so we can compare against other players
    double findBestHand(Player& comCards);
    // todo: use one function to add one card? or one to add 2?
    void addCard(Card dealt);
    // reset the player's hand, their bet and whether they folded or not 
    void resetPlayer();

    void resetBet();

    void printInfo(int iteration, int row, Player& comCards);

    // money functions
    // returns true if the player has checked/called
    virtual bool checkBetOrFold(int* betAmount, int* pot);

    void betMoney(int betAmount, int* pot);


private:
    // acts as an id for the player
    int id_;

    std::string name_;

    std::vector<Card> hand_;
    // rank the hands in order of superiority
    bool colorPrint[2];
    // used to help print the relevant cards with a correct highlight
    double handRank_;
    // amount of money player has
    int balance_;
    // amount they bet
    int bet_;
    // whether they fold (is this useful?)
    bool folded_;
    // whether they are an ai
    bool ai_;
    // ? inheritence for AI class?
};

#endif