#include <iostream>
#include "card.h"

using namespace std;

Card::Card(int id) {
    id_ = id;

    string suit[4] = {"\U00002665", "\U00002660", "\U00002666", "\U00002663"};
    int value[13] = {2,3,4,5,6,7,8,9,10,11,12,13,14};
    string type[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

    value_ = value[id_ % 13];
    suit_ = suit[id_ / 13];
    type_ = type[id_ % 13];
}
int Card::value_get() {
    return value_;
}
string Card::suit_get() {
    return suit_;
}
// bool color tells you whether to print in ___ or not (colour to be decided)
void Card::print(bool color) { // TODO: replace with operator overload?
    if((id_ / 13) % 2){
        std::cout << "\033[1;37m" ;
    }
    else{
        std::cout << "\033[1;31m" ;
    }
    std::cout << type_ << suit_ << "\033[0m";
}


bool Card::operator<(Card& rhs){
    return value_ < rhs.value_;
}
bool Card::operator>(Card& rhs){
    return value_ > rhs.value_;
}
bool Card::operator==(Card& rhs){
    return value_ == rhs.value;
}
