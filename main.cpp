#include <iostream>
using namespace std;
#include <string.h>
#include <deque>
#include <cmath>

int main(){
    int I1, I2, B;                      //Initialise Values

    struct Add{
        std::deque<int> larger;              //Initialise struct of deques to contain all numbers
        std::deque<int> smaller;
        std::deque<int> answer;
    };
    Add myStruct;

    printf("Scanning Numbers\n\n");
    scanf("%d %d %d", &I1, &I2, &B);   //Scanning for input 
    
    /*Error Checking*/

    if(B <= 1 || B > 10){
        perror("BASE ERROR");
        return 1;
    }

    //Fill deques with user input so that larger number is stored in "larger" and smaller is stored in "smaller"
    //Numbers are being stored backwards so that it is easier later to iterate through the 
    //deques and perform operations (starting from i = 0). Answer will be flipped.
    int digit;
    if(I1 > I2){
        while(I1 != 0){
            digit = I1%10;
            I1 = floor(I1/10);
            myStruct.larger.push_back(digit);
        }

        while(I2 != 0){
            digit = I2%10;
            I2 = floor(I2/10);
            myStruct.smaller.push_back(digit);
        }
    }else{
        while(I2 != 0){
            digit = I2%10;
            I2 = floor(I2/10);
            myStruct.larger.push_back(digit);
        }

        while(I1 != 0){
            digit = I1%10;
            I1 = floor(I1/10);
            myStruct.smaller.push_back(digit);
        }
    }

    int Carry = 0;
    for(int i = 0; i < myStruct.larger.size(); i++){
        if(i >= myStruct.smaller.size()){
            digit = Carry + myStruct.larger[i];
        }else{
            digit = myStruct.larger[i] + myStruct.smaller[i] + Carry;
        }
        if(digit < B){
            Carry = 0;
        }else{
            Carry = 1;
            digit = digit - B;
        }
        myStruct.answer.push_front(digit);
    }

    for(int i = 0; i < myStruct.answer.size(); i++){
        cout << myStruct.answer[i];
    };
    return 0;
}