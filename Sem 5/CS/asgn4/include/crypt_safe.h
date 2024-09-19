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

// Namespace declaration if needed
namespace cryptsafe {

class CryptSafe {
public:
    void generate_key(const std::string& file_name);
    void generate_keys_asymm(const std::string& private_key_path, const std::string& public_key_path);
    void encrypt_key_asymm(const std::string& file_path, const std::string& public_key_path);
    void decrypt_key_asymm(const std::string& file_path, const std::string& private_key_path);
    void encrypt_file_symm(const std::string& file_path,const std::string& key_path);
    void decrypt_file_symm(const std::string& file_path,const std::string& key_path);
};

} // namespace cryptsafe

#endif // CRYPT_SAFE_H