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
    cout << "\U00002665" << "\U00002660" << "\U00002666" << "\U00002663" << endl;
    cout << "\u250C" << endl;
    cout << "yay!" << endl;
    // int count = 5;
    // cin >> count;
    // cout << count << endl;
    for(int i = 0; i < 10; i++){
        if(i == 0){
            for(int j = 0; j < 12; j++){
                if(j == 0){
                    cout << "┌";
                }
                else if(j == 11){
                    cout << "┐";
                }
                else{
                    cout << "─";
                }
            }
        }
        else if(i == 9){
            for(int j = 0; j < 12; j++){
                if(j == 0){
                    cout << "└";
                }
                else if(j == 11){
                    cout << "┘";
                }
                else{
                    cout << "─";
                }
            }
        }
        else{
            cout << "│ Player 2 │";
            // for(int j = 0; j < 10; j++){
            //     if(j == 0 || j == 9){
            //         cout << "|";
            //     }
            //     else{
            //         cout << 'a';
            //     }
            // }
        }
        cout << endl;
    }
}