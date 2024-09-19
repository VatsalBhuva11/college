

#include <cryptopp/integer.h>
#include <cryptopp/osrng.h>
#include <cryptopp/nbtheory.h>
#include <cryptopp/files.h>
#include <cryptopp/modarith.h>
#include <cryptopp/hex.h>
#include <iostream>
#include <fstream>
#include <crypt_safe.h>

using namespace CryptoPP;
using namespace std;

namespace cryptsafe
{

    CryptSafe::CryptSafe()
    {
        // Constructor implementation
    }

    CryptSafe::~CryptSafe()
    {
        // Destructor implementation
    }

    void CryptSafe::SetupPhase(const std::string &publicKeyFile, const std::string &privateKeyFile)
    {
        AutoSeededRandomPool rng;

        // Generate two large prime numbers p and q
        PrimeAndGenerator pg1;
        PrimeAndGenerator pg2;
        pg1.Generate(1, rng, 1024, 3);
        pg2.Generate(1, rng, 1024, 3);
        Integer p = pg1.Prime();
        Integer q = pg2.Prime();
        cout << p << endl;
        cout << q << endl;

        // Calculate n = p * q
        Integer n = p * q;
        cout << n << endl;
        // Calculate phi(n) = (p-1) * (q-1)
        Integer phi = (p - 1) * (q - 1);
        cout << phi << endl;
        // Generate public key e such that e is coprime to phi(n)
        Integer e;
        do
        {
            e.Randomize(rng, Integer::One(), phi - 1);
        } while (GCD(e, phi) != Integer::One());

        // Calculate private key d such that e * d ≡ 1 mod phi(n)
        Integer d = e.InverseMod(phi);
        cout << d << endl;
        cout << e << endl;
        // Store public key (e, n) in publickeyFile
        FileSink publicFile(publicKeyFile.c_str());
        e.DEREncode(publicFile);
        n.DEREncode(publicFile);

        // Store private key (d, n) in privateKeyFile
        FileSink privateFile(privateKeyFile.c_str());
        d.DEREncode(privateFile);
        n.DEREncode(privateFile);
    }
    void CryptSafe::EncryptionPhase(const std::string &publicKeyFile, const std::string &plainTextFile, const std::string &cipherTextFile)
    {
        AutoSeededRandomPool rng;

        // Load public key (e, n) from the file
        Integer e, n;
        FileSource publicFile(publicKeyFile.c_str(), true);
        e.BERDecode(publicFile);
        n.BERDecode(publicFile);

        // Load the plaintext
        std::ifstream plainFile(plainTextFile);
        std::string plainText((std::istreambuf_iterator<char>(plainFile)), std::istreambuf_iterator<char>());

        // Convert plaintext to an integer
        Integer m((const CryptoPP::byte *)plainText.data(), plainText.size());

        // Encrypt the message: C ≡ m^e mod n
        Integer C = a_exp_b_mod_c(m, e, n);

        // Save the ciphertext to a file
        FileSink cipherFile(cipherTextFile.c_str());
        C.DEREncode(cipherFile);
    }

    // Function to decrypt the ciphertext using the private key (d, n)
    void CryptSafe::DecryptionPhase(const std::string &privateKeyFile, const std::string &cipherTextFile, const std::string &decryptedTextFile)
    {
        AutoSeededRandomPool rng;

        // Load private key (d, n) from the file
        Integer d, n;
        FileSource privateFile(privateKeyFile.c_str(), true);
        d.BERDecode(privateFile);
        n.BERDecode(privateFile);

        // Load the ciphertext
        Integer C;
        FileSource cipherFile(cipherTextFile.c_str(), true);
        C.BERDecode(cipherFile);

        // Decrypt the message: m ≡ C^d mod n
        Integer m = a_exp_b_mod_c(C, d, n);

        // Convert the decrypted message back to string
        size_t req = m.MinEncodedSize();
        std::string decryptedText(req, '\0');
        // encode m into the decryptedText buffer
        m.Encode((CryptoPP::byte *)decryptedText.data(), req);

        // Save the decrypted text to a file
        std::ofstream decryptedFile(decryptedTextFile);
        decryptedFile << decryptedText;
    }
}
