#include "crypt_safe.h"
#include <iostream>

int main()
{
    // Example usage
    cryptsafe::CryptSafe CS;

    std::string publicKeyFile = "publickey.bin";
    std::string privateKeyFile = "privatekey.bin";
    std::string plainTextFile = "plaintext.txt";
    std::string cipherTextFile = "ciphertext.bin";
    std::string decryptedTextFile = "decryptedtext.txt";
    std::string signatureFile = "signature.bin";
    // Perform the setup phase (key generation)
    CS.SetupPhase(publicKeyFile, privateKeyFile);

    // Perform the encryption phase
    CS.Signature(signatureFile, plainTextFile, privateKeyFile);

    // Perform the decryption phase
    CS.Verification(signatureFile, plainTextFile, publicKeyFile);

    std::cout << "Encryption and Decryption completed." << std::endl;
    return 0;
}