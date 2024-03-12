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
