#include <certificate.h>
#include <cryptopp/osrng.h>
#include <cryptopp/base64.h>
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
#include <cryptopp/dsa.h>
#include <date/date.h>
#include <chrono>
// Convert CryptoPP::RSA::PublicKey to a string
std::string PublicKeyToBase64(const CryptoPP::RSA::PublicKey &publicKey)
{
    std::string publicKeyStr;

    // Save the public key to a string
    CryptoPP::StringSink stringSink(publicKeyStr);
    publicKey.Save(stringSink);

    // Encode the binary key to Base64
    std::string encoded;
    CryptoPP::Base64Encoder encoder(new CryptoPP::StringSink(encoded), false);
    encoder.Put(reinterpret_cast<const CryptoPP::byte *>(publicKeyStr.data()), publicKeyStr.size());
    encoder.MessageEnd();

    return encoded;
}

std::string LoadPublicKeyAndConvertToBase64(const std::string &filename)
{
    using namespace CryptoPP;

    FileSource file(filename.c_str(), true /* binary mode */);
    Integer pubkey;
    pubkey.BERDecode(file);
    std::string encoded;
    
    // Encode the integer using BER encoding
    std::string berEncoded;
    CryptoPP::StringSink stringSink(berEncoded);
    pubkey.BEREncode(stringSink);
    // Encode to hex for easier viewing
        std::string encodedHex;
        CryptoPP::StringSource ss2(encoded, true,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(encodedHex)
            )
        );
    
    // // Encode the BER-encoded data to Base64
    // CryptoPP::Base64Encoder base64Encoder(new CryptoPP::StringSink(encoded), false /* no line breaks */);
    // base64Encoder.Put(reinterpret_cast<const CryptoPP::byte*>(berEncoded.data()), berEncoded.size());
    // base64Encoder.MessageEnd();
    
    return encodedHex;
}

// Wrapper method implementations for the Certificate class
void Certificate::SetIssuerDistinguishedName(const std::string &issuer)
{
    data.issuerName = issuer;
}

void Certificate::SetSubjectDistinguishedName(const std::string &subject)
{
    data.subjectName = subject;
}

void Certificate::SetNotBefore(std::string notBeforeTime)
{
    data.notBefore = notBeforeTime;
}

void Certificate::SetNotAfter(std::string notAfterTime)
{
    data.notAfter = notAfterTime;
}

void Certificate::SetSubjectPublicKey(const CryptoPP::RSA::PublicKey &key)
{
    data.publicKey = PublicKeyToBase64(key);
}

// Serialize the Certificate to a JSON string
std::string Certificate::Serialize() const
{
    nlohmann::json j;

    j["subjectName"] = data.subjectName;
    j["issuerName"] = data.issuerName;
    j["notBefore"] = data.notBefore;
    j["notAfter"] = data.notAfter;
    j["publicKey"] = data.publicKey;
    j["signatureAlgo"] = signatureAlgo;
    j["signature"] = std::string(signature.begin(), signature.end());

    return j.dump(); // Convert JSON object to string
}

std::string Certificate::SerializeData() const
{
    nlohmann::json j;
    j["subjectName"] = data.subjectName;
    j["issuerName"] = data.issuerName;
    j["notBefore"] = data.notBefore;
    j["notAfter"] = data.notAfter;
    j["publicKey"] = data.publicKey;

    return j.dump(); // Convert JSON object to string
}

// Deserialize the JSON string to a Certificate object
Certificate Certificate::Deserialize(const std::string &jsonString)
{
    nlohmann::json j = nlohmann::json::parse(jsonString);

    Certificate cert;
    cert.data.subjectName = j["subjectName"];
    cert.data.issuerName = j["issuerName"];
    cert.data.notBefore = j["notBefore"];
    cert.data.notAfter = j["notAfter"];
    cert.data.publicKey = j["publicKey"];
    cert.signatureAlgo = j["signatureAlgo"];
    cert.signature = j["signature"];

    return cert;
}

void Certificate::certificateSign(const std::string cert_file, const std::string privkeyCA, std::string notbefore, std::string notafter, std::string issuer, std::string email, std::string pubkey)
{
    using namespace CryptoPP;

    // Load the CA's private key from the file
    DSA::PrivateKey privateKey;
    try
    {
        FileSource file(privkeyCA.c_str(), true);
        privateKey.Load(file);
    }
    catch (const CryptoPP::Exception &e)
    {
        throw std::runtime_error("Failed to load CA private key: " + std::string(e.what()));
    }

    std::string user_public_key = LoadPublicKeyAndConvertToBase64(pubkey);

    this->data.issuerName = issuer;
    this->data.subjectName = email;
    this->data.notBefore = notbefore;
    this->data.notAfter = notafter;
    this->data.publicKey = user_public_key;

    // Serialize the certificate data for signing
    std::string dataToSign = this->SerializeData();

    // Initialize the signer with the CA's private key
    DSA::Signer signer(privateKey);

    // Create a signature
    // The serialized data is encrypted using CA's private key
    std::string signature;
    AutoSeededRandomPool rng;
    std::cout << "Signed Data : ";
    std::cout << dataToSign << std::endl;
    StringSource(dataToSign, true,
                 new SignerFilter(rng, signer,
                                  new StringSink(signature)));

    // Encode the signature in Base64
    std::string base64Signature;
    StringSource(signature, true, new Base64Encoder(new StringSink(base64Signature)));

    // Store the Base64 encoded signature in the certificate
    this->signature = base64Signature;

    // Save the certificate to a file
    try
    {
        std::ofstream outFile(cert_file, std::ios::binary);
        if (!outFile)
        {
            throw std::runtime_error("Failed to open certificate file for writing.");
        }

        // Write serialized data and signature to the file
        dataToSign = this->Serialize();
        outFile << dataToSign;

        outFile.close();
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Failed to save certificate: " + std::string(e.what()));
    }
}

bool Certificate::verify(const std::string certificate_file, const std::string &pub_key_filename)
{
    // Load the public key from the file
    using namespace CryptoPP;

    try
    {

        // Load the public key from a file
        DSA::PublicKey publicKey;
        FileSource pubFile(pub_key_filename.c_str(), true /*pumpAll*/);
        publicKey.Load(pubFile);

        // Decode the Base64 cert
        std::string jsonData;
        CryptoPP::FileSource file(certificate_file.c_str(), true, new CryptoPP::StringSink(jsonData));
        Certificate cert;
        cert = cert.Deserialize(jsonData);

        // Checking Certificate expiry
        std::string notAfterStr = cert.data.notAfter;
        std::cout << this->data.notAfter << std::endl;
        std::istringstream in1(notAfterStr);
        std::istringstream iss(notAfterStr);
        date::sys_days expirationDate;
        iss >> date::parse("%F", expirationDate);

        // Get the current date
        auto currentDate = date::floor<date::days>(std::chrono::system_clock::now());

        if (currentDate > expirationDate)
        {
            std::cout << "Certificate Expired" << std::endl;
            return false;
        }

        // Decode the Base64 signature

        std::string decodedSignature;
        StringSource(cert.signature, true, new Base64Decoder(new StringSink(decodedSignature)));
        std::string dataToBeVerified = cert.SerializeData();
        // Verify the signature
        DSA::Verifier verifier(publicKey);
        std::cout << "Verified Data: ";
        std::cout << dataToBeVerified << std::endl;
        bool result = verifier.VerifyMessage(
            (const byte *)dataToBeVerified.data(),
            dataToBeVerified.size(),
            (const byte *)decodedSignature.data(),
            decodedSignature.size());
        return result;
    }
    catch (const CryptoPP::Exception &e)
    {
        std::cerr << "Verification error: " << e.what() << std::endl;
        return false;
    }
}
