#ifndef CERTIFICATE_H
#define CERTIFICATE_H

#include <string>
#include <ctime>
#include <cryptopp/rsa.h>
#include <cryptopp/secblock.h>
#include <nlohmann/json.hpp>

 std::string PublicKeyToBase64(const CryptoPP::RSA::PublicKey& publicKey) ;

class Data {
public:
    std::string subjectName;
    std::string issuerName;
    std::string notBefore;
    std::string notAfter;
    std::string publicKey;
};

class Certificate {
public:
    Data data;
    std::string signatureAlgo="DSA";
    std::string signature;

    // Wrapper methods for Data's methods
    void SetIssuerDistinguishedName(const std::string& issuer);
    void SetSubjectDistinguishedName(const std::string& subject);
    void SetNotBefore(std::string notBeforeTime);
    void SetNotAfter(std::string notAfterTime);
    void SetSubjectPublicKey(const CryptoPP::RSA::PublicKey& key);
    void certificateSign(const std::string certificate,const std::string privkeyCA, std::string notbefore, std::string notafter,std::string issuer, std:: string email, std:: string pubkey);
    bool verify(const std::string certificate,const std::string& pub_key);
    // Serialization and Deserialization methods
    std::string Serialize() const;
    std::string SerializeData() const;
    Certificate Deserialize(const std::string& jsonString);

};

#endif // CERTIFICATE_H
