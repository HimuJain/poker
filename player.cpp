#include <iostream>
#include <stdexcept>
#include "card.h"
#include "player.h"
using namespace std;
Player::Player() : idNum_(0), name_("Doe"), balance_(0), ai_(false){
}
Player::Player(int id, string name, int balance, bool AI = false) : idNum_(id), name_(name), balance_(balance), ai_(AI) {
}

// hand functions

// ? if there is a valid hand, then the cards are highlighted; will the comCards print too?
void Player::printHand(){
    for(int i = 0; i < hand_.size(); i++){
        hand_[i].print();
    }
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

// reset the bet amount for a new round

void Player::resetBet(){
    bet_ = 0;
}

// money functions


bool Player::checkBetOrFold(int* betAmount, int* pot){
    int choice;
    if(folded_){
        cout << "Player " << idNum_ << ", " << name_ << " has folded. " << endl;
        return;
    }
    // use to reset menu if player wants to go back to the menu
    bool finished = false;
    while(!finished){
        cout << "Player " << idNum_ << ", " << name_ << ", would you like to bet/raise (1), check/call (2) or fold (3)?" << endl;
        // checking for a valid choice
        while(!(cin >> choice) || (choice < 1 || choice > 3)){
            cout << "Please enter a valid choice." << endl;
            continue;
        }
        
        if(choice == 1){
            cout << "How much would you like to bet? (New bet must be less than the balance and at should add at least twice your call.) To go back, input -1." << endl;
            int newBet;
            bool valid = false;
                while(!valid){

                    cin >> newBet >> endl;
                    if(newBet == -1){
                        break;
                    }
                    else if(newBet > balance_){
                        cout << "You do not have enough money to bet that amount (balance: " << balance_ << "). Please enter a valid amount." << endl;
                        continue;
                    }
                    else if(newBet - bet_ < 2*(*betAmount - bet_)){
                        cout << "You must bet an additional amount that is at least twice your call (min bet " << (*betAmount - bet_) + *betAmount << ").  Please enter a valid amount." << endl;
                        continue;
                    }
                    else if(newBet < 0){
                        cout << "Invalid amount. Please enter a valid amount." << endl;
                        continue;
                    }
                    else{
                        valid = true;
                    }

                }

                if(newBet == -1){
                    continue;
                }

                betMoney((newBet - bet_), pot);
                bet_ = newBet;
                return false; // because player has bet/raised and so has to go around again
        }

        else if(choice == 2){
            if(bet_ == *betAmount){
                cout << "Player " << idNum_ << ", " << name_ << " has checked." << endl;
            }
            else if(bet_ < *betAmount){
                cout << "Player " << idNum_ << ", " << name_ << " has called." << endl;
                betMoney((*betAmount - bet_), pot);
                bet_ = *betAmount;
            }
            return true; // because player has checked/called and so can move on
        }

        else if(choice == 3){
            folded_ = true;
            cout << "Player " << idNum_ << ", " << name_ << " has folded." << endl;
            return true; // because player has folded and so can move on
        }
    }
    
}  

void Player::betMoney(int betAmount, int* pot){
    balance_ -= betAmount;
    *pot += betAmount;
}