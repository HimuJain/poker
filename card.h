#include <iostream>

const enum Colors {BLANK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE, GREY};

class Card {
public:
    Card() { id_ = -1; }
    Card(int id);
    int value_get();
    char* suit_get();
    void print(bool color = false);
private:
    int id_;
    int value_;
    char* suit_;
    char* type_;
};
Card::Card(int id) {
    id_ = id;

    char* suit[4] = {"\U00002665", "\U00002660", "\U00002666", "\U00002663"};
    int value[13] = {2,3,4,5,6,7,8,9,10,11,12,13,14};
    char* type[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

    value_ = value[id_ % 13];
    suit_ = suit[id_ / 13];
    type_ = type[id_ % 13];
}
int Card::value_get() {
    return value_;
}
char* Card::suit_get() {
    return suit_;
}
// bool color tells you whether to print in red or not
void Card::print(bool color = false) {
    if(color){
        std::cout << "\033[1;31m";
    }
    std::cout << type_ << suit_ << ' ' << "\033[0m";
}
