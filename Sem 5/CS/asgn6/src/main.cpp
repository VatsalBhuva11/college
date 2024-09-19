#include "crypt_safe.h"
#include "../../asgn5/include/certify_me.h"
#include <iostream>
#include <string>
#include "../../asgn5/include/certificate.h" // Include your certificate handling classes/headers

int main()
{
    cryptsafe::CryptSafe cryptSafe;
    certifyme::CertifyMe certifyMe;
    Certificate certA;
    Certificate certB;
    // Generate a symmetric key and save it to a file
    cryptSafe.setup(1024, 160);
    cryptSafe.gen_priv();
    cryptSafe.gen_pub();
    certifyMe.generate_CA_pub_priv_key("CA");

    certA.certificateSign("cert1", "CA_priv.key", "2002-12-10", "2025-10-10", "iiita", "vatsalbhuva11@gmail.com", "publicKeyA.bin");
    certB.certificateSign("cert2", "CA_priv.key", "2002-12-10", "2025-10-10", "iiita", "vatsalbhuva12@gmail.com", "publicKeyB.bin");

    Certificate cert_A_rec;
    Certificate cert_B_rec;

    std::string jsonDataA;
    CryptoPP::FileSource file1("cert1", true, new CryptoPP::StringSink(jsonDataA));
    cert_A_rec = cert_A_rec.Deserialize(jsonDataA);

    std::string jsonDataB;
    CryptoPP::FileSource file2("cert2", true, new CryptoPP::StringSink(jsonDataB));
    cert_B_rec = cert_B_rec.Deserialize(jsonDataB);

    if (!cert_A_rec.verify("cert1", "CA_pub.key"))
    {
        std::cout << "Not Verified A" << std::endl;
        return -1;
    }
    if (!cert_B_rec.verify("cert2", "CA_pub.key"))
    {
        std::cout << "Not Verified B" << std::endl;
        return -1;
    }

    std::cout << "Verified" << std::endl;

    cryptSafe.GenerateSharedSecretKey(cert_A_rec.data.publicKey, "privatekeyB.bin", "publicKeyA.bin", "KA.bin");
    cryptSafe.GenerateSharedSecretKey(cert_B_rec.data.publicKey, "privatekeyA.bin", "publicKeyB.bin", "KB.bin");

    return 0;
}