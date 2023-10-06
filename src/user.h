#ifndef USER_H
#define USER_H

#include <string>
#include <libcryptosec/RSAKeyPair.h>
#include <libcryptosec/Signer.h>
#include <libcryptosec/certificate/Certificate.h>
#include "constants.h"

using namespace std;

/**
 * @brief Represents a user of the application.
 */
class User
{
private:
    string name;
    string password;
    Certificate* certificate;
    PrivateKey* privateKey;
    PublicKey* publicKey;
    RDNSequence subjectInfo;

public:
    User(pair<string, string> userCredentials);

    User(string name,
        string passwrord,
        Certificate* certificate,
        PrivateKey* privateKey);

    ~User();

    /**
     * @brief Set the user's certificate.
     */
    void setCertificate(Certificate* certificate);

    /**
     * @brief Validades the user's password.
     */
    bool authenticate(string password);

    /**
     * @brief Signs a hash with the user's private key.
     */
    ByteArray sign(Signer* signer, ByteArray& hash);

    /**
     * @brief Issues a certificate request.
     */
    CertificateRequest issueRequest();

    /**
     * @brief Getter for the user's certificate.
     */
    Certificate* getCertificate();

    /**
     * @brief Getter for the user's username.
     */
    const string getName();

    /**
     * @brief Saves the user's certificate to a p12 file.
     */
    bool save();
};

#endif // !USER_H