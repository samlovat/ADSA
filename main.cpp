#include <iostream>
using namespace std;
#include <string.h>
#include <cmath>

string mult(string I1, string I2, int B){
    int digit;
    int carry = 0;
    string answer = "Multiplication didnt work";
    if(I1.length() >= I2.length()){
        answer = "";
        for(int i = 0; i < I1.length(); i++){
            digit = (I1[I1.length()-1-i] - '0')*(I2[0] - '0') + carry;
            if(digit >= B){
                carry = floor(digit/B);
                digit = digit%B;
            }else{
                carry = 0;
            }
            //Prepend next digit to front of answer
            answer = to_string(digit) + answer;
        }
        answer = to_string(carry) + answer;
    }else{
        answer = "";
        for(int i = 0; i < I2.length(); i++){
            digit = (I2[I2.length()-1-i] - '0')*(I1[0] - '0') + carry;
            if(digit >= B){
                carry = floor(digit/B);
                digit = digit%B;
            }else{
                carry = 0;
            }
            //Prepend next digit to front of answer
            answer = to_string(digit) + answer;
        }
        answer = to_string(carry) + answer;
    }
    return answer;
}

string add(string I1, string I2, int B){
    string answer;
    int length1 = I1.length();
    int length2 = I2.length();
    int digit;
    int Carry = 0;
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
            answer = to_string(digit) + answer;
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
            answer = to_string(digit) + answer;
        }
    }

    //Catch any remaining carry
    if(Carry == 1){
        answer = '1' + answer;
    }
    return answer;
}

string karatsuba(string I1, string I2, int B){
    string answer;
    //Find Length of numbers
    int n = max(I1.length(), I2.length());

    //Base Case for n = 1
    if(I1.length() == 1 || I2.length() == 1){
        answer = mult(I1, I2, B);
        return answer;
    }
    
    //Append leading zeros if needed 
    int numOfAppend;
    if(I1.length() != n){
        numOfAppend = n - I1.length();
        for(int i = 0; i < numOfAppend; i++){
            I1 = '0' + I1; 
        }
    }else{
        numOfAppend = n - I2.length();
        for(int i = 0; i < numOfAppend; i++){
            I2 = '0' + I2; 
        }
    }

    //split numbers into parts 
    string x1, x0, y1, y0;
    int half = ceil(n/2);

    for(int i = 0; i < n; i++){
        if(i < half){
            x1 += I1[i];
            y1 += I2[i];
        }else{
            x0 += I1[i];
            y0 += I2[i];
        }
    }

    cout << "\n\nx0: " << x0 << "\nx1: " << x1 << "\ny0: " << y0 << "\ny1: " << y1 << endl;
    
    //Make z2, z1 and z0
    string z2, z1, z0;

    //Recursive call to z's
    z2 = karatsuba(x1, y1, B);
    z1 = karatsuba(x1, y0, B);
    z0 = karatsuba(x0, y0, B);

    //Append zeros for return
    for(int i = 0; i < n; i++){
        z2 += '0';
    }
    for(int i = 0; i < half; i++){
        z1 += '0';
    }

    answer = add(add(z2, z1, B), z0, B);
    //return
    return answer;
}

int main(){
    string I1;                      //Initialise Values
    string I2;
    int B;
    
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


    //Only start calculating length of I1 or I2 once leading zeroes are accounted for
    
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
    string ansadd = add(I1, I2, B);
    string ansmult = karatsuba(I1, I2, B);
    cout << "\n\nAnsadd: " << ansadd << endl;
    cout << "\n\nAnsmult: " << ansmult << endl;
    
    return 0;
}