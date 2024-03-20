#include <iostream>
#include "card.h"
#include "player.h"
using namespace std;
Player::Player(){
    idNum_ = 0;
    name_ = "Doe";
    balance_ = 0;
    ai_ = false;
}
Player::Player(int id, string name, int balance, bool AI = false){
    idNum_ = id;
    name_ = name;
    balance_ = balance;
    ai_ = AI;
}

// hand functions

// ? if there is a valid hand, then the cards are highlighted; will the comCards print too?
void Player::printHand(){
    
}
// todo: should have a return value so we can compare against other players
double Player::findBestHand(Player comCards){

}
void Player::addCard(Card dealt){
    hand_.push_back(dealt);
}
// reset the player's hand, their bet and whether they folded or not 
void Player::resetPlayer(){
    hand_.clear();
    bet_ = 0;
    folded_ = false;
}

// money functions

void Player::checkBetOrFold(int* betAmount, int* pot){
    char choice;
    cout << "Would you like to bet (b), check (c) or fold (f)?" << endl;
    cin >> choice;
    
}  

