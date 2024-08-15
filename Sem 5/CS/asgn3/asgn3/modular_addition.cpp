#include <iostream>
#include <cryptopp/integer.h>
#include <cryptopp/osrng.h>

using namespace std;
using namespace CryptoPP;

int main()
{
    // Define two large integers using CryptoPP::Integer
    Integer a("1234567890123456789012345678901234567890");
    Integer b("9876543210987654321098765432109876543210");

    // Define the modulus for modular arithmetic
    Integer modulus("10000000000000000000000000000000000000007");

    // Perform modular addition: (a + b) % modulus
    Integer result = (a + b) % modulus;

    // Print the result
    cout << "Result of (a + b) % modulus: " << result << endl;

    return 0;
}
