

#include <cryptopp/integer.h>
#include <cryptopp/osrng.h>
#include <cryptopp/nbtheory.h>
#include <cryptopp/files.h>
#include <cryptopp/modarith.h>
#include <cryptopp/hex.h>
#include <cryptopp/md5.h>
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

    bool compareHashes(const std::string &hash1_file, const std::string &hash2_file)
    {

        std::ifstream f1(hash1_file, std::ios::binary);
        std::ifstream f2(hash2_file, std::ios::binary);
        if (!f1.is_open())
        {
            std::cerr << "Error: Could not open file " << hash1_file << std::endl;
            return false;
        }
        if (!f2.is_open())
        {
            std::cerr << "Error: Could not open file " << hash2_file << std::endl;
            return false;
        }
        char ch1, ch2;
        while (f1.get(ch1) && f2.get(ch2))
        {
            if (ch1 != ch2)
            {
                return false;
            }
        }
        return true;
    }

    void CryptSafe::SetupPhase(const std::string &publicKeyFile, const std::string &privateKeyFile)
    {
        AutoSeededRandomPool rng;

        PrimeAndGenerator pg1;
        PrimeAndGenerator pg2;
        pg1.Generate(1, rng, 1024, 3);
        pg2.Generate(1, rng, 1024, 3);
        Integer p = pg1.Prime();
        Integer q = pg2.Prime();
        cout << p << endl;
        cout << q << endl;

        Integer n = p * q;
        cout << n << endl;
        Integer phi = (p - 1) * (q - 1);
        cout << phi << endl;

        // selecting public key as "e"
        Integer e;
        do
        {
            e.Randomize(rng, Integer::One(), phi - 1);
        } while (GCD(e, phi) != Integer::One());

        // calculating private key as "d" from "e"
        Integer d = e.InverseMod(phi);
        cout << d << endl;
        cout << e << endl;
        FileSink publicFile(publicKeyFile.c_str());
        e.DEREncode(publicFile);
        n.DEREncode(publicFile);
        FileSink privateFile(privateKeyFile.c_str());
        d.DEREncode(privateFile);
        n.DEREncode(privateFile);
    }
    void CryptSafe::EncryptionPhase(const std::string &publicKeyFile, const std::string &plainTextFile, const std::string &cipherTextFile)
    {
        AutoSeededRandomPool rng;

        Integer e, n;
        FileSource publicFile(publicKeyFile.c_str(), true);
        e.BERDecode(publicFile);
        n.BERDecode(publicFile);

        std::ifstream plainFile(plainTextFile);
        std::string plainText((std::istreambuf_iterator<char>(plainFile)), std::istreambuf_iterator<char>());

        Integer m((const CryptoPP::byte *)plainText.data(), plainText.size());

        Integer C = a_exp_b_mod_c(m, e, n);

        FileSink cipherFile(cipherTextFile.c_str());
        C.DEREncode(cipherFile);
    }

    void CryptSafe::DecryptionPhase(const std::string &privateKeyFile, const std::string &cipherTextFile, const std::string &decryptedTextFile)
    {
        AutoSeededRandomPool rng;

        Integer d, n;
        FileSource privateFile(privateKeyFile.c_str(), true);
        d.BERDecode(privateFile);
        n.BERDecode(privateFile);

        Integer C;
        FileSource cipherFile(cipherTextFile.c_str(), true);
        C.BERDecode(cipherFile);

        Integer m = a_exp_b_mod_c(C, d, n);

        size_t req = m.MinEncodedSize();
        std::string decryptedText(req, '\0');
        m.Encode((CryptoPP::byte *)decryptedText.data(), req);

        std::ofstream decryptedFile(decryptedTextFile);
        decryptedFile << decryptedText;
    }

    void CryptSafe::MD5Hash(const std::string &hashed_file, const std::string &file_to_be_hashed)
    {
        MD5 md5;
        std::string digest;

        try
        {
            FileSource(file_to_be_hashed.c_str(), true,
                       new HashFilter(md5,
                                      new HexEncoder(
                                          new StringSink(digest),
                                          false)));
            std::ofstream out_file(hashed_file);
            if (out_file.is_open())
            {
                out_file << digest;
                out_file.close();
                std::cout << "MD5 checksum written to " << hashed_file << std::endl;
            }
            else
            {
                std::cerr << "Error: Could not open output file." << std::endl;
            }
        }
        catch (const Exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    void CryptSafe::Signature(const std::string &signature_file, const std::string &plainTextFile, const std::string &privatekey_file)
    {
        // for signature, hash the message first and store in msgHash1.bin .
        this->MD5Hash("msgHash1.bin", plainTextFile);
        // then, sign it using priv key and store in signature_file
        this->EncryptionPhase(privatekey_file, "msgHash1.bin", signature_file);
    }
    void CryptSafe::Verification(const std::string &signature_file, const std::string &messageFile, const std::string &publickeyfile)
    {

        // hash received message and store in msgHash2.bin (message is in messageFile)
        this->MD5Hash("msgHash2.bin", messageFile);
        // decrypt received signature to obtain the hash of sent message. stored in verification_hash.bin
        this->DecryptionPhase(publickeyfile, signature_file, "verification_hash.bin");

        if (compareHashes("verification_hash.bin", "msgHash2.bin"))
        {
            cout << "VERIFICATION SUCCESSFULL" << endl;
        }
        else
        {
            cout << "VERIFICATION FAILED" << endl;
        }
    }
}
