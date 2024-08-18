#include <iostream>
using namespace std;
#include <string.h>
#include <cmath>

string mult(string I1, string I2, int B){
    int digit;                                      //Digit var to hold and calculate each digit of answer 
    int carry = 0;                                  //Tracks if carry over occurs 
    string answer;    
    if(I1.length() >= I2.length()){
        for(size_t i = 0; i < I1.length(); i++){
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
        for(size_t i = 0; i < I2.length(); i++){
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
    string answer;                              //Initialise answer
    int length1 = I1.length();                  //Store lengths of numbers
    int length2 = I2.length();
    int digit;                                  //Variable to store each digit calculation
    int Carry = 0;                              //Variable that tracks carry over 
    
    if(I1.length() >= I2.length()){                                             //If the length of I1 is larger than or equal to I2 
        for(size_t i = 0; i < I1.length(); i++){                                //loop iterates n times where n is the num of digits in I1
            if(i >= I2.length()){                           //If all of I2 has been handled stop trying to access I2 (avoid seg faults)
                digit = Carry + I1[length1-1-i] - '0';      // - '0' to convert to integer form 
            }else{
                digit = I1[length1-1-i] + I2[length2-1-i] + Carry - '0' - '0';      //Addition of corresponding digits in I1, I2 and any Carry
            }                                                                       // - '0' to convert to integer form 
            if(digit < B){
                Carry = 0;                      //If new digit is smaller than Base B, no carry over
            }else{                      
                Carry = 1;                      //Otherwise, there is carry over, change state of Carry for next loop iteration
                digit = digit - B;              //Alter digit value to account for the carry over
            }
            answer = to_string(digit) + answer; //Prepend new digit to the answer (must convert to string first)
        }
    }else{
        for(size_t i = 0; i < I2.length(); i++){                //Same Operations if I2 is larger than I1
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

    if(Carry == 1){                                 
        answer = '1' + answer;                 //Catch any remaining carry
    }
    return answer;
}

string subt(string I1, string I2, int B){

    string larger, smaller, answer;             //Variable Initialisation, larger and smaller to determine which number should be 
    int digit, digit1, digit2;                  //subtracted from the other. Digit variables to calculate each digit of answer 
    int sameNumber = 1;                         //To check if they are the same number, i.e. larger and smaller wouldn't be assigned during the following for loop

    if(I1.length() != I2.length()){             //If I1 and I2 aren't the same length, prepend zeros as necessary to the shorter number 
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
    for(size_t i = 0; i < I1.length(); i++){                    //Now that numbers are same length, iterate through to check which 
        if((I1[i] - '0') < (I2[i] - '0')){                      //number is larger and smaller respectively 
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

    if(sameNumber == 1){                        //If sameNumber variable wasn't updated, the numbers must be the same and '0' is outputted
        answer = '0';
        return answer;
    }

    int steal = 0;                                              //Steal variable, equivalent to carry for addition and multiplication
    for(size_t i = 0; i < smaller.length(); i++){               
        if(steal != 1){                                         //If there was no carry needed from previous iteration
            digit1 = larger[larger.length()-1-i] - '0';         
            digit2 = smaller[smaller.length()-1-i] - '0';       //digits 1 and 2 used to avoid errors during calculation 
            digit = digit1 - digit2;                            //Calculate value of new digit
        }else{
            digit1 = larger[larger.length()-1-i] - '0';
            digit2 = smaller[smaller.length()-1-i] - '0';
            digit = digit1 - digit2 - 1;                        //If previous iteration required carry over, reduce calculation by 1
            steal = 0;
        }
        if(digit < 0){                                          //Check for carry
            digit += B;                                         
            steal = 1;                                          //Set steal variable to affect next iteration
        }           
        answer = to_string(digit) + answer;                     //Stringify digit for answer prepending 
    }
    return answer;    
}

string karatsuba(string I1, string I2, int B){
    string answer;
    float n = max(I1.length(), I2.length());                //Find max length of two numbers (n)
    if(I1.length() == 1 || I2.length() == 1){               //Base Case 
        answer = mult(I1, I2, B);                           //Use regular multiplication when one of numbers has 1 digit
        return answer;
    }
    
    int numOfAppend;
    if(I1.length() != n){                                   //Append leading zeros if needed 
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

    string x1, x0, y1, y0;
    int half = ceil(n/2);
    for(int i = 0; i < n; i++){                 //Split numbers into parts 
        if(i < floor(n/2)){
            x1 += I1[i];
            y1 += I2[i];
        }else{
            x0 += I1[i];
            y0 += I2[i];
        }
    }

    string P0, P1, P2;                                      //Recursive calls to karatsuba to calculate P0, P1 and P2
    P0 = karatsuba(x0, y0, B);
    P1 = karatsuba(x1, y1, B);
    P2 = karatsuba((add(x0, x1, B)), add(y0, y1, B), B);
    string sub = subt(subt(P2, P1, B), P0, B);              //Subtract to find P2 - P1 - P0

    for(int i = 0; i < (half*2); i++){                      //Append zeros for return 
        P1 += '0';
    }
    for(int i = 0; i < half; i++){
        sub += '0';
    }

    answer = add(add(P1, sub, B), P0, B);                   //Final Calculation 
    return answer;
}

int main(){
    string I1;                      //Initialise Values
    string I2;
    int B;
    cin >> I1;                      //Scanning for values
    cin >> I2;
    cin >> B;

    if(B <= 1 || B > 10){
        perror("BASE ERROR");       //Error Checking
        return 1;
    }

    string ansadd = add(I1, I2, B);                             //Function Calls
    string ansmult = karatsuba(I1, I2, B);
    
    int leadingZero;
    for(size_t i = 0; i < ansmult.length(); i++){               //Cleans answer of leading zeros
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
    std::cout << ansadd << " " << ansmult << " 0" << endl;      //Output as Required 
    return 0;
}