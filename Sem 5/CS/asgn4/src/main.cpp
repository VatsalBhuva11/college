#include "crypt_safe.h"
#include <iostream>

int main()
{
    cryptsafe::CryptSafe cryptSafe;

    // Generate a symmetric key and save it to a file
    cryptSafe.generate_key("symmetric.key");
    cryptSafe.generate_keys_asymm("private.key", "public.key");
    // Encrypt the symmetric key using an asymmetric public key
    cryptSafe.encrypt_key_asymm("symmetric.key", "public.key");

    // Decrypt the symmetric key using an asymmetric private key
    cryptSafe.decrypt_key_asymm("symmetric.key.enc", "private.key");

    // // Encrypt a file using the symmetric key
    cryptSafe.encrypt_file_symm("test.jpeg", "symmetric.key");

    // // Decrypt the file using the symmetric key
    cryptSafe.decrypt_file_symm("test.jpeg.enc", "symmetric.key.enc.dec");

    std::cout << "Encryption and decryption completed successfully." << std::endl;

    return 0;
}