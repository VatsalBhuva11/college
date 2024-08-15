#include <cryptopp/osrng.h>
#include <cryptopp/sha.h>
#include <cryptopp/base64.h>
#include <stdio.h>
#include <iostream>

using namespace CryptoPP;
using namespace std;

string SHA256HashString(string aString)
{
    // String to store the digest (hash result)
    string digest;
    // Create a SHA-256 hash object
    SHA256 hash;

    // StringSource takes the input message
    // HashFilter performs the hash and redirects the output to a Base64Encoder
    // HexEncoder converts the hash result to a readable hex format
    // StringSink stores the output in the digest string
    StringSource foo(aString, true,
                     new HashFilter(hash,
                                    new Base64Encoder(
                                        new StringSink(digest))));

    return digest;
}

int main()
{
    string s = "Hello world, this is Vatsal!";
    string hash = SHA256HashString(s);
    cout << "Hash of the string: " << hash;
}