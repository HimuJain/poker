#include <iostream>
#include <stdexcept>
#include "card.h"
#include "player.h"
using namespace std;
Player::Player() : id_(0), name_("Doe"), handRank_(0), balance_(0), ai_(false){
    for(int i = 0; i < 2; i++){
        colorPrint[i] = false;
    }
}
Player::Player(int id, string name, int balance, bool AI) : id_(id), name_(name), handRank_(0), balance_(balance), ai_(AI) {
    for(int i = 0; i < 2; i++){
        colorPrint[i] = false;
    }
}

Player::~Player(){
}

// hand functions

// ? if there is a valid hand, then the cards are highlighted; will the comCards print too?
void Player::printHand(){
    for(int i = 0; i < hand_.size(); i++){
        hand_[i].print();
        if(i != hand_.size() - 1){
            cout << " ";
        }
    }
}
// todo: should have a return value so we can compare against other players
double Player::findBestHand(Player& comCards){
    // should be run before the info gets printed (to allow for accurate colouring)
    // * need to find a way to track the order/track the cards? to allow for proper colouring? (or just search through?)
    vector<Card> allCards;
    vector<int> cardDiff;
    vector<int> suits;
    allCards.insert(allCards.end(), hand_.begin(), hand_.end());
    allCards.insert(allCards.end(), comCards.hand_.begin(), comCards.hand_.end());

    return handRank_;
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

void Player::printInfo(int iteration, int row, Player& comCards){
    // ! take into account the fact that cards can have 3 digits instead of 2 (only the case for 10)

    bool turn = (id_ == iteration);

    int idFind = id_;
    int idLen = 0;
    while(idFind != 0){
        idFind /= 10;
        idLen++;
    }
    // it's 7 + idLen + 2 + name size because that's the length of the player print case: Player #: """"
    int nameLen = 7 + idLen + 2 + name_.size();
    int largestLength = nameLen;

    int balFind = balance_;
    int balLen = 0;
    while(balFind != 0){
        balFind /= 10;
        balLen++;
    }
    if(balLen == 0){
        balLen = 1;
    }
    // it's 9 + balLen because that's the length of the balance print case: Balance: """
    if(9 + balLen > largestLength){
        largestLength = 9 + balLen;
    }
    balLen += 9;

    int handLen = 19;
    for(int i = 0; i < 2; i++){
        if(hand_[i].value_get() == 10){
            handLen += 1;
        }
    }
    // it's handLen because that's the length of the player cards print case: Player Cards: "" "" (taking into account the 10 case)
    if(handLen > largestLength){
        largestLength = handLen;
    }

    int betLen = 0;
    int betFind = bet_;
    while(betFind != 0){
        betFind /= 10;
        betLen++;
    }
    if(betLen == 0){
        betLen = 1;
    }
    // it's 5 + betLen because that's the length of the bet print case: Bet: """
    if(5 + betLen > largestLength){
        largestLength = 5 + betLen;
    }
    betLen += 5;

    int comCardsSize = 0;
    if(turn && (comCards.hand_).size() > 0 && largestLength < 16 + ((comCards.hand_).size() * 3)){ // if it is their turn, take the length of comCards into account
        largestLength = 16 + ((comCards.hand_).size() * 3);
        comCardsSize = 16 + ((comCards.hand_).size() * 3);
        for(int i = 0; i < 3; i++){
            if(comCards.hand_[i].value_get() == 10){
                largestLength += 1;
                comCardsSize += 1;
            }
        }
    }

    // that was all for finding the largest possible string of characters that could be printed so an adequate box size can be printed
    if(row == 0){
        for(int i = 0; i < largestLength + 4; i++){
            if(turn){
                if(i == 0){
                    cout << "\033[1;36m╔";
                }
                else if(i == largestLength + 3){
                    cout << "╗\033[0m";
                }
                else{
                    cout << "═";
                }
            }
            else{
                if(i == 0){
                    cout << "┌";
                }
                else if(i == largestLength + 3){
                    cout << "┐";
                }
                else{
                    cout << "─";
                }
            }
        }
    }
    else if(row == 1){
        if(turn){
            cout << "\033[1;36m║\033[0m Player " << id_ << ": " << name_;
        }
        else{
            cout << "│ Player " << id_ << ": " << name_;
        }
        for(int i = 0; i < largestLength - nameLen; i++){
            cout << " ";
        }
        if(turn){
            cout << " \033[1;36m║\033[0m";
        }
        else{
            cout << " │";
        }
    }
    else if(row == 2){
        if(turn){
            cout << "\033[1;36m║\033[0m Balance: \033[1;32m" << balance_;
        }
        else{
            cout << "│ Balance: \033[1;32m" << balance_;
        }
        for(int i = 0; i < largestLength - balLen; i++){
            cout << " ";
        }
        if(turn){
            cout << "\033[0m \033[1;36m║\033[0m";
        }
        else{
            cout << "\033[0m │";
        }
    }
    else if(row == 3){
        if(turn && (comCards.hand_).size() > 0){
            cout << "\033[1;36m║\033[0m Community Cards: " ;
            comCards.printHand(); 
        }
        else if (turn){
            cout << "\033[1;36m║\033[0m ";
        }
        else{
            cout << "│ ";
        }
        for(int i = 0; i < largestLength - comCardsSize; i++){
            cout << " ";
        }
        if(turn){
            cout << " \033[1;36m║\033[0m";
        }
        else{
            cout << " │";
        }
    }
    else if(row == 4){
        if(turn){
            cout << "\033[1;36m║\033[0m Player Cards: " ;
            printHand(); 
            for(int i = 0; i < largestLength - handLen; i++){
            cout << " ";
            }
        }
        else if(folded_){
            cout << "│ Player Cards: " ;
            printHand(); 
            for(int i = 0; i < largestLength - handLen; i++){
            cout << " ";
            }
        }
        else{
            cout << "│ Player Cards: ?? ??";
            for(int i = 0; i < largestLength - 19; i++){
            cout << " ";
            }
        }
        if(turn){
            cout << " \033[1;36m║\033[0m";
        }
        else{
            cout << " │";
        }
    }
    else if(row == 5){
        if(turn){
            cout << "\033[1;36m║\033[0m Bet: \033[1;34m" << bet_;
        }
        else{
            cout << "│ Bet: \033[1;34m" << bet_;
        }
        for(int i = 0; i < largestLength - betLen; i++){
            cout << " ";
        }
        if(turn){
            cout << "\033[0m \033[1;36m║\033[0m";
        }
        else{
            cout << "\033[0m │";
        }
    }
    else if(row == 6){
        for(int i = 0; i < largestLength + 4; i++){
            if(turn){
                if(i == 0){
                    cout << "\033[1;36m╚";
                }
                else if(i == largestLength + 3){
                    cout << "╝\033[0m";
                }
                else{
                    cout << "═";
                }
            }
            else{
                if(i == 0){
                    cout << "└";
                }
                else if(i == largestLength + 3){
                    cout << "┘";
                }
                else{
                    cout << "─";
                }
            }
        }
    }

}


// money functions


bool Player::checkBetOrFold(int* betAmount, int* pot){
    if(!ai_){
        int choice;
        if(folded_){
            cout << "Player " << id_ << ", " << name_ << " has folded. " << endl;
            return true; // player has already folded so no extra actions necessary
        }
        // use to reset menu if player wants to go back to the menu
        bool finished = false;
        while(!finished){
            cout << "Player " << id_ << ", " << name_ << ", would you like to bet/raise (1), check/call (2) or fold (3)?" << endl;
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

                        if(cin.fail()){
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(),'\n');
                            // got i wish i could use cin >> ws, but ws ALSO clears newlines, so it wouldn't work
                        }

                        cin >> newBet;
                        if(newBet == -1){
                            break;
                        }
                        else if(newBet > balance_){
                            cout << "You do not have enough money to bet that amount (balance: " << balance_ << "). Please enter a valid amount." << endl;
                            continue;
                        }
                        else if(newBet < 0 || cin.fail()){
                            cout << "Invalid amount. Please enter a valid amount." << endl;
                            continue;
                        }
                        else if(newBet - bet_ < 2*(*betAmount - bet_)){
                            cout << "You must bet an additional amount that is at least twice your call (min bet " << (*betAmount - bet_) + *betAmount << ").  Please enter a valid amount." << endl;
                            continue;
                        }
                        else{
                            valid = true;
                        }
                    }

                    if(newBet == -1){
                        continue;
                    }


                    betMoney((newBet), pot);
                    *betAmount = newBet;
                    return false; // because player has bet/raised and so has to go around again
            }

            else if(choice == 2){
                if(bet_ == *betAmount){
                    cout << "Player " << id_ << ", " << name_ << " has checked." << endl;
                }
                else if(bet_ < *betAmount){
                    cout << "Player " << id_ << ", " << name_ << " has called." << endl;
                    betMoney((*betAmount), pot);
                }
                return true; // because player has checked/called and so can move on
            }

            else if(choice == 3){
                folded_ = true;
                cout << "Player " << id_ << ", " << name_ << " has folded." << endl;
                return true; // because player has folded and so can move on
            }
        }
    }
    return false; // some error: find a better value to return?
}  
// ! double check the bet/call functionality and the use of a helper function
// ! directly in the main poker code
void Player::betMoney(int betAmount, int* pot){
    balance_ -= (betAmount - bet_);
    *pot += (betAmount - bet_);
    bet_ = betAmount;
}