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

string subt(string I1, string I2, int B){

    string larger, smaller, answer;
    int digit, digit1, digit2;

    //To check if they are the same number, i.e. larger and smaller wouldn't be assigned during the following for loop
    int sameNumber = 1;
    //Determine which number is larger 
    //If both are the same length, compare digits from most significant to least significant
    //Both should be the same length since zeros have been appended as necessary for karatsuba before the subt function call
    if(I1.length() != I2.length()){
        int lengthDif;
        if(I1.length() < I2.length()){
            lengthDif = I2.length() - I1.length();
            for(int i = 0; i < lengthDif; i++){
                I1 = '0' + I1;
            }
        }else{
            lengthDif = I1.length() - I2.length();
            for(int i = 0; i < lengthDif; i++){
                I2 = '0' + I2;
            }
        }
    }
    for(int i = 0; i < I1.length(); i++){
        if((I1[i] - '0') < (I2[i] - '0')){
            larger = I2;
            smaller = I1;
            sameNumber = 0;
            break;
        }else if((I2[i] - '0') < (I1[i] - '0')){
            larger = I1;
            smaller = I2;
            sameNumber = 0;
            break;
        }
    }

    if(sameNumber == 1){
        answer = '0';
        return answer;
    }


    //Subtraction
    int steal = 0;
    for(int i = 0; i < smaller.length(); i++){
        if(steal != 1){
            digit1 = larger[larger.length()-1-i] - '0'; 
            digit2 = smaller[smaller.length()-1-i] - '0';
            digit = digit1 - digit2;
        }else{
            digit1 = larger[larger.length()-1-i] - '0';
            digit2 = smaller[smaller.length()-1-i] - '0';
            digit = digit1 - digit2 - 1;
            steal = 0;
        }
        if(digit < 0){
            digit += B;
            steal = 1;
        }
        answer = to_string(digit) + answer;
    }
    return answer;    
}

string karatsuba(string I1, string I2, int B){
    string answer;
    static int counter = 0;
    counter++;
    //Find Length of numbers
    float n = max(I1.length(), I2.length());
    std::cout << "Karatsuba Call Num: " << counter << "\nFor the I1 and I2 of " << I1 << " and " << I2 << ". The n value is " << n << endl;

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
        if(i < floor(n/2)){
            x1 += I1[i];
            y1 += I2[i];
        }else{
            x0 += I1[i];
            y0 += I2[i];
        }
    }

    cout << "x0: " << x0 << " x1: " << x1 << " y0: " << y0 << " y1: " << y1 << endl;
    
    //Make z2, z1 and z0
    string P0, P1, P2;

    //Recursive call to z's
    P0 = karatsuba(x0, y0, B);
    P1 = karatsuba(x1, y1, B);
    P2 = karatsuba((add(x0, x1, B)), add(y0, y1, B), B);
    std::cout << "Karatsuba Num: " << counter << ". \nP0: " << P0 << " P1: " << P1 << "P2: " << P2 << endl;
    //Subtract to find P2 - P1 - P0
    string sub = subt(subt(P2, P1, B), P0, B);
    std::cout << "Sub Val: " << sub << endl;

    //Append zeros for return
    for(int i = 0; i < (half*2); i++){
        P1 += '0';
    }
    for(int i = 0; i < half; i++){
        sub += '0';
    }

    answer = add(add(P1, sub, B), P0, B);
    std::cout << "Final Calculation: P1*10^n: " << P1 << " ()*10^n/2: " << sub << " P0: " << P0 << endl;
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

    //Cleans ansmult of leading zeros
    int leadingZero;
    for(int i = 0; i < ansmult.length(); i++){
        if(ansmult[i] == '0'){
            leadingZero = 1;
        }else{
            if(leadingZero != 1){
                break;
            }
            ansmult = ansmult.substr(i, ansmult.length()-i);
            break;
        }
    }
    std::cout << ansadd << " " << ansmult << " 0" << endl;   

    // string test = mult("8", "71827387", 9); 
    // std::cout << "\n\nTEST RESULTS: " << test << endl;
    return 0;
}