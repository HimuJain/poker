#include <iostream>
using namespace std;
int main(){
    cout << "\033[1;31mThis text is red.\033[0m" << endl;
    cout << "\033[1;32mThis text is green.\033[0m" << endl;
    cout << "\033[1;33mThis text is yellow.\033[0m" << endl;
    cout << "\033[1;34mThis text is blue.\033[0m" << endl;
    cout << "\033[1;35mThis text is magenta.\033[0m" << endl;
    cout << "\033[1;36mThis text is cyan.\033[0m" << endl;
    cout << "\033[1;37mThis text is white.\033[0m" << endl;
    cout << "\033[1;90mThis text is grey.\033[0m" << endl;
    cout << "yay!" << endl;
    int count = 5;
    cin >> count;
    cout << count << endl;
    return 0;
}