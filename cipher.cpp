#include <iostream>
using namespace std;

int main(){
    char cost;
    cin >> cost;
    int costASCII = (int)cost;
    if(costASCII <= 90){
        costASCII = costASCII - 65;
    }else{
        costASCII = costASCII - 71;
    }
    cout << costASCII << endl;
    return 0;
}