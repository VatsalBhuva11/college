#include "crypt_safe.h"
#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include <cryptopp/files.h>
#include <cryptopp/hex.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>

namespace cryptsafe {

// generate AES key (symmetric)
void CryptSafe::generate_key(const std::string& file_name) {
    using namespace CryptoPP;
    AutoSeededRandomPool rng;
    SecByteBlock key(AES::DEFAULT_KEYLENGTH);
    rng.GenerateBlock(key, key.size());
    // Save key to file
    /*
    The FileSink constructor (from the Crypto++ library) requires a 
    C-style string (const char*) as an argument to specify the file name.
    file_name.c_str() converts the std::string to a const char* so it 
    can be used with the FileSink constructor.
    */
    FileSink file(file_name.c_str());
    file.Put(key, key.size());
}

// generate RSA public/private keys (asymmetric)
void CryptSafe::generate_keys_asymm(const std::string& private_key_path, const std::string& public_key_path) {
    using namespace CryptoPP;
    AutoSeededRandomPool rng;

    // Generate private key
    InvertibleRSAFunction privateKey;

    /*
    privateKey.Initialize(rng, 2048): This initializes the private key 
    with the random number generator rng and a key size of 2048 bits. 
    The key size of 2048 bits is a common choice for secure RSA keys.
    */
    privateKey.Initialize(rng, 2048);
    RSA::PrivateKey rsaPrivateKey(privateKey);
    FileSink privFile(private_key_path.c_str());
    privateKey.DEREncode(privFile);

    // Generate public key
    RSA::PublicKey rsaPublicKey(rsaPrivateKey);
    FileSink pubFile(public_key_path.c_str());
    rsaPublicKey.DEREncode(pubFile);
}

//encrypt the AES key using RSA public key
void CryptSafe::encrypt_key_asymm(const std::string& file_path, const std::string& public_key_path) {
    
    using namespace CryptoPP;
    AutoSeededRandomPool rng;
    // Load public key
    RSA::PublicKey publicKey;
    FileSource pubFile(public_key_path.c_str(), true);
    publicKey.Load(pubFile);

    // Load key
    SecByteBlock key(AES::DEFAULT_KEYLENGTH);
    FileSource keyFile(file_path.c_str(), true);
    keyFile.Get(key, key.size());

    // Encrypt key
    RSAES_OAEP_SHA_Encryptor encryptor(publicKey);
    size_t encSize = encryptor.CiphertextLength(key.size());
    SecByteBlock encKey(encSize);
    encryptor.Encrypt(rng, key, key.size(), encKey);

    // Save encrypted key to file
    FileSink encFile((file_path + ".enc").c_str());
    encFile.Put(encKey, encKey.size());
} 

//decrypt AES key using RSA private key
void CryptSafe::decrypt_key_asymm(const std::string& file_path, const std::string& private_key_path) {
    

    using namespace CryptoPP;
    AutoSeededRandomPool rng;
    // Load private key
    RSA::PrivateKey privateKey;
    FileSource privFile(private_key_path.c_str(), true);
    privateKey.Load(privFile);

    // Load encrypted key
    SecByteBlock encKey;
    FileSource encFile(file_path.c_str(), true);
    encKey.resize(encFile.MaxRetrievable());
    encFile.Get(encKey, encKey.size());

    // Decrypt key
    RSAES_OAEP_SHA_Decryptor decryptor(privateKey);
    size_t decSize = decryptor.MaxPlaintextLength(encKey.size());
    SecByteBlock decKey(decSize);
    decryptor.Decrypt(rng, encKey, encKey.size(), decKey);
    size_t decLength=decKey.size();
    // Save decrypted key to file
    FileSink decFile((file_path + ".dec").c_str());
    decFile.Put(decKey, decLength);
}

// encrypt image using AES key
void CryptSafe::encrypt_file_symm(const std::string& file_path, const std::string& key_path) {
    using namespace CryptoPP;

    // Load the AES key from the key file
    SecByteBlock key(AES::DEFAULT_KEYLENGTH);
    FileSource keyFile(key_path.c_str(), true);
    keyFile.Get(key, key.size());

    // Generate a random IV
    AutoSeededRandomPool rng;
    byte iv[AES::BLOCKSIZE];
    rng.GenerateBlock(iv, sizeof(iv));

    /*
    in AES, first block xored with random IV. then subsequent blocks xored 
    with previous blocks. then all these blocks are encrypted using AES.
    */

    // Set up AES encryption in CBC mode
    CBC_Mode<AES>::Encryption encryption;
    encryption.SetKeyWithIV(key, key.size(), iv);

    // Encrypt the file
    std::string encrypted_file_path = file_path + ".enc";
    FileSource fs(file_path.c_str(), true,
        new StreamTransformationFilter(encryption,
            new FileSink(encrypted_file_path.c_str())
        )
    );

    // Save the IV to a separate file
    std::string iv_file_path = file_path + ".iv";
    FileSink ivFile(iv_file_path.c_str());
    ivFile.Put(iv, sizeof(iv));
}

void CryptSafe::decrypt_file_symm(const std::string& file_path, const std::string& key_path) {
    using namespace CryptoPP;

    // Load the AES key from the key file
    SecByteBlock key(AES::DEFAULT_KEYLENGTH);
    FileSource keyFile(key_path.c_str(), true);
    keyFile.Get(key, key.size());

    // Load the IV from the corresponding .iv file
    std::string iv_file_path = file_path.substr(0, file_path.find_last_of('.')) + ".iv";
    byte iv[AES::BLOCKSIZE];
    FileSource ivFile(iv_file_path.c_str(), true);
    ivFile.Get(iv, sizeof(iv));

    // Set up AES decryption in CBC mode
    CBC_Mode<AES>::Decryption decryption;
    decryption.SetKeyWithIV(key, key.size(), iv);

    // Decrypt the file
    std::string decrypted_file_path = file_path.substr(0, file_path.find_last_of('.')) + ".dec";
    FileSource fs(file_path.c_str(), true,
        new StreamTransformationFilter(decryption,
            new FileSink(decrypted_file_path.c_str())
        )
    );
}

}