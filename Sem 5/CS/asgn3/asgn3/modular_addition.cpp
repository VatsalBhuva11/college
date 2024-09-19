#include <iostream>
#include <cryptopp/integer.h>

using namespace std;
using namespace CryptoPP;

int main()
{
    // Define two large integers using CryptoPP::Integer
    string firstNum, secondNum;
    cout << "Enter first number: ";
    cin >> firstNum;
    cout << "Enter second number: ";
    cin >> secondNum;
    Integer a(firstNum.c_str());
    Integer b(secondNum.c_str());

    string modStr;
    cout << "Enter modulus: ";
    cin >> modStr;
    // Define the modulus for modular arithmetic
    Integer modulus(modStr.c_str());

    // Perform modular addition: (a + b) % modulus
    Integer result = (a + b) % modulus;

    // Print the result
    cout << "Result of (a + b) % modulus: " << result << endl;

    return 0;
}
