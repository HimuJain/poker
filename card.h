#ifndef CARD
#define CARD

#include <iostream>

// enum Colors {BLANK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE, GREY};

class Card {
public:
    Card() { id_ = -1; }
    Card(int id);
    int value_get();
    std::string suit_get();
    bool operator<(Card& rhs);
    bool operator>(Card& rhs);
    bool operator==(Card& rhs);
    void print(bool color = false);
private:
    int id_;
    int value_;
    std::string suit_;
    std::string type_;
};

#endif