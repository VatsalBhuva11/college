#ifndef CRYPT_SAFE_H
#define CRYPT_SAFE_H

// Include necessary libraries
#include <string>
#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include <cryptopp/files.h>
#include <cryptopp/hex.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/integer.h>

// Namespace declaration if needed
namespace cryptsafe
{

    // Class declaration
    class CryptSafe
    {
    public:
        // Constructor
        CryptSafe();

        // Destructor
        ~CryptSafe();

        // Member functions
        void SaveInteger(std::ofstream &outFile, const CryptoPP::Integer &value);
        void LoadInteger(std::ifstream &inFile, CryptoPP::Integer &value);
        void GeneratePrivateKeys(const CryptoPP::Integer &p, const std::string &fileNameA, const std::string &fileNameB);
        void GeneratePublicKey(const CryptoPP::Integer &g, const CryptoPP::Integer &p, const std::string &privateKeyFile, const std::string &publicKeyFile);
        void setup(int pSize, int qSize);
        void gen_priv();
        void gen_pub();
        void GenerateSharedSecretKey(const std::string &publicKeyStr, const std::string &privateKeyFile, const std::string &publicKeyFile, const std::string &outputFile);
        // void GenerateSharedSecretKeyB(const std::string &publicKeyStr, const std::string &privateKeyFile, const std::string &outputFile);
    };

} // namespace cryptsafe

#endif // CRYPT_SAFE_H