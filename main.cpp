#include <iostream>
using namespace std;
#include <string.h>
#include <deque>
#include <cmath>

int main(){
    string I1;                      //Initialise Values
    string I2;
    int B;
    std::deque<int> ans;
    // struct Add{
    //     std::deque<int> larger;              //Initialise struct of deques to contain all numbers
    //     std::deque<int> smaller;
    //     std::deque<int> answer;
    // };
    // Add myStruct;
    
    //Scanning for values
    cin >> I1;
    cin >> I2;
    cin >> B;
    // cout << "I1: " << I1 << "\n\nI2: " << I2 << "\n\nB: " << B << endl;

    /*Error Checking*/

    if(B <= 1 || B > 10){
        perror("BASE ERROR");
        return 1;
    }

    //Fill deques with user input so that larger number is stored in "larger" and smaller is stored in "smaller"
    //Numbers are being stored backwards so that it is easier later to iterate through the 
    //deques and perform operations (starting from i = 0). Answer will be flipped.

    //Only start calculating length of I1 or I2 once leading zeroes are accounted for
    int length1 = I1.length();
    int length2 = I2.length();
    /*
    int counter; 
    int leadingZeros = 1;
    while(leadingZeros == 1){
        if(I1[counter] == '\0'){
            break;
        }
        if(I1[counter] == '0'){
            counter++;
        }else{
            leadingZeros = 0;
        }
    }
    length1 = I1.length() - counter;

    counter = 0;
    leadingZeros = 1;
    while(leadingZeros == 1){
        if(I2[counter] == '\0'){
            break;
        }
        if(I2[counter] == '0'){
            counter++;
        }else{
            leadingZeros = 0;
        }
    }
    length2 = I2.length() - counter;

    if(length1 > length2){

    }
    digit = I2[counter] - '0';
    myStruct.larger.push_back(digit);
    counter++;
    length1++;

    leadingZeros = 1;
    counter = 0;
    while(I2[counter] != '\0'){
        while(leadingZeros == 1){
            if(I2[counter] == '\0'){
                break;
            }
            digit = I1[counter] - '0';
            myStruct.larger.push_back(digit);
            counter++;
            if(digit != 0){
                leadingZeros = 0;
            }
        }
        digit = I1[counter] - '0';
        myStruct.larger.push_back(digit);
        counter++;
        length1++;
    }
    */
    int digit;
    int Carry = 0;
    int larger;
    if(I1.length() >= I2.length()){
        for(int i = 0; i < I1.length(); i++){
            if(i >= I2.length()){
                digit = Carry + I1[length1-1-i] - '0';
            }else{
                digit = I1[length1-1-i] + I2[length2-1-i] + Carry - '0' - '0';
            }
            if(digit < B){
                Carry = 0;
            }else{
                Carry = 1;
                digit = digit - B;
            }
            ans.push_front(digit);
        }
    }else{
        for(int i = 0; i < I2.length(); i++){
            if(i >= I1.length()){
                digit = Carry + I2[length2-1-i] - '0';
            }else{
                digit = I2[length2-1-i] + I1[length1-1-i] + Carry - '0' - '0';
            }
            if(digit < B){
                Carry = 0;
            }else{
                Carry = 1;
                digit = digit - B;
            }
            ans.push_front(digit);
        }
    }
    if(Carry == 1){
        ans.push_front(1);
    }
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i];
    };
    
    return 0;
}