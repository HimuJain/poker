#include <iostream>
using namespace std;
int main(){
    cout << "\033[1;30mThis text is red.\033[0m" << endl;
    cout << "\033[1;32mThis text is green.\033[0m" << endl;
    cout << "\033[1;33mThis text is yellow.\033[0m" << endl;
    cout << "\033[1;34mThis text is blue.\033[0m" << endl;
    cout << "\033[1;35mThis text is magenta.\033[0m" << endl;
    cout << "\033[1;36mThis text is cyan.\033[0m" << endl;
    cout << "\033[1;37mThis text is white.\033[0m" << endl;
    cout << "\033[1;90mThis text is grey.\033[0m" << endl;
    cout << "yay!" << endl;
    return 0;
}