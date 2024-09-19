
#include "certify_me.h"
#include <iostream>
#include <string>
#include "certificate.h" // Include your certificate handling classes/headers

/*
- certificate contains server data, signature (encrypted hash of data), server public key
- signature is encrypted using CA's private key
- when client accesses server, client decrypts signature using CA's public key to obtain hash
- then client also generates hash using same algo of data, and compares hashes to see
if certificate was forged.
- once verified, server's public key is obtained.
- server and client have a secret. client sends the secret to server by encrypting using
server's public key (present in certificate). only server can decrypt with it's priv key
- now symmetric tunnel is established. both generate the same symmetric key using the
same secret.
*/

void print_usage()
{
    std::cout << "Usage: ./app <operation> [arguments]\n";
    std::cout << "Operations:\n";
    std::cout << "1. Generate CA Keys: ./app 1 <ca_key_filename>\n";
    std::cout << "2. Generate User Keys: ./app 2 <user_key_filename>\n";
    std::cout << "3. Sign Certificate: ./app 3 <certificate_file> <ca_private_key_file> <notbefore yyyy-mm-dd> <notafter yyyy-mm-dd> <issuername> <email> <server_pub_file>\n";
    std::cout << "4. Verify Certificate: ./app 4 <certificate_file> <ca_public_key_file>\n";
}

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        print_usage();
        return 1;
    }

    int operation = std::stoi(argv[1]);

    switch (operation)
    {
    case 1: // Generate CA Keys
        if (argc != 3)
        {
            print_usage();
            return 1;
        }
        else
        {
            std::string ca_filename = argv[2];
            certifyme::CertifyMe certifyMe;
            certifyMe.generate_CA_pub_priv_key(ca_filename);
            std::cout << "CA keys generated successfully.\n";
        }
        break;

    case 2: // Generate User Keys
        if (argc != 3)
        {
            print_usage();
            return 1;
        }
        else
        {
            std::string user_filename = argv[2];
            certifyme::CertifyMe certifyMe;
            certifyMe.generate_user_pub_priv_key(user_filename); // Assuming same function for simplicity
            std::cout << "User keys generated successfully.\n";
        }
        break;

    case 3: // Sign Certificate
        if (argc != 9)
        {
            print_usage();
            return 1;
        }
        else
        {
            std::string cert_file = argv[2];
            std::string ca_priv_key_file = argv[3];
            std::string notbefore = argv[4];
            std::string notafter = argv[5];
            std::string issuer = argv[6];
            std::string email = argv[7];
            std::string pubkey = argv[8];
            Certificate cert;
            cert.certificateSign(cert_file, ca_priv_key_file, notbefore, notafter, issuer, email, pubkey);
            std::cout << "Certificate signed successfully.\n";
        }
        break;

    case 4: // Verify Certificate
        if (argc != 4)
        {
            print_usage();
            return 1;
        }
        else
        {
            std::string cert_file = argv[2];
            std::string ca_pub_key_file = argv[3];
            Certificate cert;
            bool is_verified = cert.verify(cert_file, ca_pub_key_file);
            if (is_verified)
            {
                std::cout << "Certificate verification successful.\n";
            }
            else
            {
                std::cout << "Certificate verification failed.\n";
            }
        }
        break;

    default:
        print_usage();
        return 1;
    }

    return 0;
}
