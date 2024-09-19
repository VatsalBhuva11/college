#include "certify_me.h"
#include <cryptopp/dsa.h>
#include <cryptopp/rsa.h>
#include <ctime>
#include <cryptopp/osrng.h>
#include <cryptopp/files.h>
#include <cryptopp/hex.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/pssr.h>
#include <cryptopp/rsa.h>
#include <cryptopp/secblock.h>

namespace certifyme {

CertifyMe::CertifyMe() {
    // Constructor implementation
}

CertifyMe::~CertifyMe() {
    // Destructor implementation
}

void CertifyMe::generate_CA_pub_priv_key(std::string file_name) {
    using namespace CryptoPP;

    try {
        AutoSeededRandomPool rng;

        // Generate DSA private key
        DSA::PrivateKey dsaPrivateKey;
        dsaPrivateKey.GenerateRandomWithKeySize(rng, 2048); // Use a suitable key size
        FileSink privFile((file_name + "_priv.key").c_str());
        dsaPrivateKey.Save(privFile);

        // Generate DSA public key
        DSA::PublicKey dsaPublicKey;
        dsaPublicKey.AssignFrom(dsaPrivateKey);
        FileSink pubFile((file_name + "_pub.key").c_str());
        dsaPublicKey.Save(pubFile);

        std::cout << "DSA keys generated and saved successfully." << std::endl;
    } catch (const CryptoPP::Exception& e) {
        std::cerr << "Error generating DSA keys: " << e.what() << std::endl;
    }
}
void CertifyMe::generate_user_pub_priv_key(std::string file_name) {
    using namespace CryptoPP;
     AutoSeededRandomPool rng;
    // Generate private key
    InvertibleRSAFunction privateKey;
    privateKey.Initialize(rng, 1024);
    RSA::PrivateKey rsaPrivateKey(privateKey);
    FileSink privFile((file_name+"_priv.key").c_str());
    privateKey.DEREncode(privFile);

    // Generate public key
    RSA::PublicKey rsaPublicKey(rsaPrivateKey);
    FileSink pubFile((file_name+"_pub.key").c_str());
    rsaPublicKey.DEREncode(pubFile);
}
}