#include "crypt_safe.h"
#include <cryptopp/rsa.h>

#include <cryptopp/files.h>
#include <cryptopp/hex.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>

#include <iostream>
#include <fstream>
#include <cryptopp/integer.h>
#include <cryptopp/osrng.h>
#include <cryptopp/dh.h>
#include <cryptopp/nbtheory.h>
#include <cryptopp/algparam.h>
#include <cryptopp/base64.h>

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
    using namespace CryptoPP;
    using namespace std;

    // modular exponentiation
    Integer ModExp(const Integer &base, const Integer &exponent, const Integer &modulus)
    {
        Integer result = 1;
        Integer b = base % modulus;
        Integer e = exponent;

        while (e > 0)
        {
            if (e.GetBit(0))
            {
                result = (result * b) % modulus;
            }
            e >>= 1;
            b = (b * b) % modulus;
        }
        return result;
    }

    // Function to perform Miller-Rabin primality test
    // a probabilistic test, meaning there's a small chance of error.
    /*
    If n is less than 2, it returns false. If n is 2 or 3, it returns true.
    If n is even, it returns false. It expresses n−1 as 2 s ×d, where d is odd.
    For each round, it picks a random integer a and checks whether a^d modn is
    either 1 or n−1.
    If not, it checks whether any of the successive squarings of x
    result in n−1.
    If it fails the test in any round, it returns false;
    otherwise, it returns true.
    */

    bool IsProbablePrime(const Integer &n, RandomNumberGenerator &rng, unsigned int rounds = 10)
    {
        if (n < 2)
            return false;
        if (n == 2 || n == 3)
            return true;
        if (n % 2 == 0)
            return false;

        Integer d = n - 1;
        Integer s = 0;
        while (d % 2 == 0)
        {
            d >>= 1;
            s += 1;
        }

        for (unsigned int i = 0; i < rounds; i++)
        {
            Integer a;
            a.Randomize(rng, 1, n - 1); // Random number in range [1, n-1]

            Integer x = ModExp(a, d, n);
            if (x == 1 || x == n - 1)
                continue;

            bool continueLoop = false;
            for (Integer r = 0; r < s; r++)
            {
                x = ModExp(x, Integer(2), n);
                if (x == n - 1)
                {
                    continueLoop = true;
                    break;
                }
            }

            if (!continueLoop)
                return false;
        }

        return true;
    }

    // Function to generate a prime number with the specified number of bits
    /*
    A random number is generated with the required number of bits.
    The most significant bit (MSB) is set to ensure the number is large enough.
    If the number is even, it is incremented to make it odd.
    The function repeatedly generates numbers until one passes the IsProbablePrime test.
    */
    Integer GeneratePrime(size_t numBits)
    {
        AutoSeededRandomPool prng; // Random number generator

        Integer prime;
        while (true)
        {
            // Generate a random number with the desired number of bits
            prime.Randomize(prng, numBits / 8);

            // Ensure the number is within the desired bit length
            prime |= (Integer(1) << (numBits - 1)); // Set the most significant bit (MSB)

            // Ensure the number is odd
            if (prime.GetBit(0) == 0)
            {
                prime += 1; // Make it odd by adding 1
            }

            // Check if the generated number is prime
            if (IsProbablePrime(prime, prng))
            {
                return prime;
            }
        }
    }

    // Function to generate a prime p where p - 1 is divisible by q
    Integer GeneratePrimeWithCondition(size_t numBits, const Integer &q, RandomNumberGenerator &rng)
    {
        Integer k;
        Integer p;
        size_t kBits = numBits - q.BitCount(); // Estimate bits needed for k
        AutoSeededRandomPool prng;
        while (true)
        {
            k.Randomize(rng, kBits / 8);
            k |= (Integer(1) << (kBits - 1)); // Ensure k has enough bits

            p = k * q + 1; // then, p-1 will be divisible by q

            // Ensure p has the correct number of bits
            if (IsProbablePrime(p, prng, 20))
            {
                return p;
            }
        }
    }

    // Function to find a generator of a cyclic group of order q
    /*
    The function generates random candidates in the range [2,p−1].
    It checks if g=candidate ^ (p−1)/q modp is not equal to 1, meaning the candidate
    is a valid generator. If a valid generator is found, it returns the candidate.
    */
    Integer FindGenerator(const Integer &q, const Integer &p)
    {
        Integer candidate;
        AutoSeededRandomPool rng;
        int iterate = 100;
        while (iterate--)
        {
            // Generate a random candidate in the range [1, q-1]
            candidate.Randomize(rng, 2, p - 1);

            // Check if result is 1, which means the candidate is a generator
            if (ModExp(candidate, (p - 1) / q, p) != Integer(1))
            {
                return candidate;
            }
        }

        return candidate;
    }

    // Function to save integers to a binary file
    /*
    Each integer is encoded into a byte array.
    The size of each encoded integer is written to the file,
    followed by the encoded data itself.
    This allows for easy retrieval of the parameters later.
    */
    void SaveIntegersToFile(const std::string &filename, const Integer &p, const Integer &q, const Integer &g)
    {
        // Open file for binary writing
        std::ofstream file(filename, std::ios::binary);
        if (!file)
        {
            std::cerr << "Error opening file for writing: " << filename << std::endl;
            return;
        }

        // Serialize each Integer to a byte array
        std::string pStr(p.MinEncodedSize(), 0);
        std::string qStr(q.MinEncodedSize(), 0);
        std::string gStr(g.MinEncodedSize(), 0);

        p.Encode(reinterpret_cast<CryptoPP::byte *>(&pStr[0]), pStr.size());
        q.Encode(reinterpret_cast<CryptoPP::byte *>(&qStr[0]), qStr.size());
        g.Encode(reinterpret_cast<CryptoPP::byte *>(&gStr[0]), gStr.size());

        // Write sizes followed by the data
        size_t pSize = pStr.size();
        size_t qSize = qStr.size();
        size_t gSize = gStr.size();

        file.write(reinterpret_cast<const char *>(&pSize), sizeof(size_t));
        file.write(pStr.data(), pSize);

        file.write(reinterpret_cast<const char *>(&qSize), sizeof(size_t));
        file.write(qStr.data(), qSize);

        file.write(reinterpret_cast<const char *>(&gSize), sizeof(size_t));
        file.write(gStr.data(), gSize);

        file.close();
    }
    void CryptSafe::SaveInteger(std::ofstream &outFile, const CryptoPP::Integer &value)
    {
        using namespace CryptoPP;
        using namespace std;
        size_t encodedSize = value.MinEncodedSize();
        unique_ptr<CryptoPP::byte[]> encodedValue(new CryptoPP::byte[encodedSize]);
        value.Encode(encodedValue.get(), encodedSize);
        outFile.write(reinterpret_cast<char *>(encodedValue.get()), encodedSize);
    }

    void CryptSafe::LoadInteger(std::ifstream &inFile, CryptoPP::Integer &value)
    {
        using namespace CryptoPP;
        using namespace std;
        std::streampos fileSize;
        inFile.seekg(0, std::ios::end);
        fileSize = inFile.tellg();
        inFile.seekg(0, std::ios::beg);

        unique_ptr<CryptoPP::byte[]> buffer(new CryptoPP::byte[fileSize]);
        inFile.read(reinterpret_cast<char *>(buffer.get()), fileSize);
        value.Decode(buffer.get(), fileSize);
    }

    void CryptSafe::setup(int pSize, int qSize)
    {
        using namespace CryptoPP;

        size_t numBitsP = pSize;
        size_t numBitsQ = qSize;

        try
        {

            AutoSeededRandomPool rng;
            /*
            q is generated as a 160-bit prime. p is generated such that
            p−1 is divisible by q. g is found as a generator modulo p.
            */
            Integer q = GeneratePrime(numBitsQ);
            Integer p = GeneratePrimeWithCondition(numBitsP, q, rng);
            Integer g = FindGenerator(q, p);
            cout << p << '\n';
            cout << q << '\n';
            cout << g << '\n';
            // Save to file
            FileSink file("params.bin", true);
            p.DEREncode(file);
            q.DEREncode(file);
            g.DEREncode(file);

            cout << "Setup Done" << endl;
        }
        catch (const Exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
            exit(-1);
        }
        // Store g, p, q in a binary file
    }

    void CryptSafe::GeneratePrivateKeys(const CryptoPP::Integer &p, const std::string &fileNameA, const std::string &fileNameB)
    {
        using namespace CryptoPP;
        AutoSeededRandomPool rng;

        // Generate private keys α and β (values between 1 and p-1)
        Integer privateKeyA = Integer(rng, 1, p - 1);
        Integer privateKeyB = Integer(rng, 1, p - 1);
        cout << privateKeyA << " " << privateKeyB << endl;
        // Save privateKeyA
        std::ofstream outFileA(fileNameA, std::ios::binary);
        if (outFileA.is_open())
        {
            SaveInteger(outFileA, privateKeyA);
            outFileA.close();
        }
        else
        {
            std::cerr << "Error: Unable to open file " << fileNameA << std::endl;
        }

        // Save privateKeyB
        std::ofstream outFileB(fileNameB, std::ios::binary);
        if (outFileB.is_open())
        {
            SaveInteger(outFileB, privateKeyB);
            outFileB.close();
        }
        else
        {
            std::cerr << "Error: Unable to open file " << fileNameB << std::endl;
        }
    }

    Integer generatePrivateKey(const Integer &q)
    {
        AutoSeededRandomPool rng;
        // priv key is random number in group [1,q-1]
        return Integer(rng, Integer::One(), q - 1);
    }

    // Private key generation for Alice and Bob
    void CryptSafe::gen_priv()
    {
        // Reading parameters from params.bin
        // parameters are : p, q, and g
        FileSource file("params.bin", true /* binary mode */);
        Integer p, q, g;
        p.BERDecode(file);
        q.BERDecode(file);
        g.BERDecode(file);

        // Generate private keys
        Integer alpha = generatePrivateKey(q);
        Integer beta = generatePrivateKey(q);

        // Saving the private keys to files
        FileSink fileA("privatekeyA.bin", true /* binary mode */);
        alpha.DEREncode(fileA);
        FileSink fileB("privatekeyB.bin", true /* binary mode */);
        beta.DEREncode(fileB);

        cout << "Private keys generated and saved." << endl;
    }

    Integer generatePublicKey(const Integer &privateKey, const Integer &p, const Integer &g)
    {
        // g^privKey % p
        // generate public key from private key
        return a_exp_b_mod_c(g, privateKey, p);
    }

    // Public key generation for Alice and Bob
    void CryptSafe::gen_pub()
    {
        // Reading parameters from params.bin
        FileSource paramsFile("params.bin", true /* binary mode */);

        Integer p, q, g;
        p.BERDecode(paramsFile);
        q.BERDecode(paramsFile);
        g.BERDecode(paramsFile);

        // Reading Alice's private key from privatekeyA.bin
        FileSource privateKeyAFile("privatekeyA.bin", true /* binary mode */);
        Integer alpha;
        alpha.BERDecode(privateKeyAFile);

        // Reading Bob's private key from privatekeyB.bin
        FileSource privateKeyBFile("privatekeyB.bin", true /* binary mode */);
        Integer beta;
        beta.BERDecode(privateKeyBFile);

        // Generate public keys
        Integer K_A = generatePublicKey(alpha, p, g);
        Integer K_B = generatePublicKey(beta, p, g);

        // Writing Alice's public key to publicKeyA.bin
        FileSink publicKeyAFile("publicKeyA.bin", true /* binary mode */);
        K_A.DEREncode(publicKeyAFile);

        // Writing Bob's public key to publicKeyB.bin
        FileSink publicKeyBFile("publicKeyB.bin", true /* binary mode */);
        K_B.DEREncode(publicKeyBFile);
        cout << alpha << " " << beta << endl;
        cout << "Public keys generated and saved." << endl;
    }

    Integer Base64ToInteger(const std::string &base64Str)
    {
        // Step 1: Decode the Base64 string into raw binary data
        std::string decoded;
        StringSource ss(base64Str, true /*pumpAll*/);
        Base64Decoder decoder;
        decoder.Attach(new StringSink(decoded));
        ss.TransferTo(decoder);
        decoder.MessageEnd();

        // Step 2: Convert the binary data to a CryptoPP::Integer
        Integer integer(reinterpret_cast<const byte *>(decoded.data()), decoded.size());

        return integer;
    }
    void CryptSafe::GenerateSharedSecretKey(const std::string &publicKeyStr, const std::string &privateKeyFile, const std::string &publicKeyFile, const std::string &outputFile)
    {

        Integer publicKey = Base64ToInteger(publicKeyStr);
        FileSource paramsFile("params.bin", true /* binary mode */);

        Integer p, q, g;
        p.BERDecode(paramsFile);
        q.BERDecode(paramsFile);
        g.BERDecode(paramsFile);

        // Read the private key from file
        Integer privateKey;
        FileSource privateKeySource(privateKeyFile.c_str(), true /* binary mode */);
        privateKey.BERDecode(privateKeySource);

        // Compute the shared secret key
        Integer pubKey;
        FileSource pubKeySource(publicKeyFile.c_str(), true /* binary mode */);
        pubKey.BERDecode(pubKeySource);

        Integer sharedSecretKey = a_exp_b_mod_c(pubKey, privateKey, p);
        cout << "Secret key: " << sharedSecretKey << endl;
        // cout << publicKey << " " << privateKey << " " << p << endl;
        // Save the shared secret key to file
        FileSink outputFileSink(outputFile.c_str(), true /* binary mode */);
        sharedSecretKey.DEREncode(outputFileSink);

        cout << "Shared secret key generated and saved to " << outputFile << endl;
    }

}
