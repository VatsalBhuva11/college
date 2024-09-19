#ifndef CRYPT_SAFE_H
#define CRYPT_SAFE_H

// Include necessary libraries

#include <cryptopp/integer.h>
#include <cryptopp/osrng.h>
#include <cryptopp/nbtheory.h>
#include <cryptopp/files.h>
#include <cryptopp/modarith.h>
#include <cryptopp/hex.h>
#include <iostream>
#include <fstream>

// Namespace declaration if needed
namespace cryptsafe {

// Class declaration
class CryptSafe {
public:
    // Constructor
    CryptSafe();

    // Destructor
    ~CryptSafe();

    // Member functions
    void SetupPhase(const std::string& publicKeyFile, const std::string& privateKeyFile);
    void EncryptionPhase(const std::string& publicKeyFile, const std::string& plainTextFile, const std::string& cipherTextFile);
    void DecryptionPhase(const std::string& privateKeyFile, const std::string& cipherTextFile, const std::string& decryptedTextFile);
    void MD5Hash(const std::string& hashed_file, const std::string& file_to_be_hashed);
    void Signature(const std::string& signature_file, const std::string& plainTextFile, const std::string& privatekey_file);
    void Verification(const std::string& hashed_file, const std::string& messageFile, const std::string& publickeyfile);
};

} // namespace cryptsafe

#endif // CRYPT_SAFE_H