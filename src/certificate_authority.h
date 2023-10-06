#ifndef CERTIFICATE_AUTHORITY_H
#define CERTIFICATE_AUTHORITY_H

#include <iostream>
#include <libcryptosec/RSAKeyPair.h>
#include <libcryptosec/certificate/RDNSequence.h>
#include <libcryptosec/certificate/CertificateBuilder.h>
#include <libcryptosec/Pkcs12.h>
#include "user.h"


using namespace std;


/**
 * @brief Represents the application's certificate authority.
 * 
 * @details The certificate authority is responsible for issuing certificates
 * for the application's users. It also issues its own certificate.
 */
class CertificateAuthority
{
private:
    PrivateKey* privateKey;
    PublicKey* publicKey;
    Certificate* authCertificate;
    string name = "certauth";
    string password = "admin";

public:
    /**
     * @details Initializes the certificate authority's credentials for issuing
     * certificates.
     */
    CertificateAuthority();

    CertificateAuthority(Pkcs12* pkcs12);

    ~CertificateAuthority();

    /**
     * @brief Issues the Certificate Authority's own certificate.
     */
    void emitOwnCertificate();

    /**
     * @brief Issues a certificate for a user.
     * 
     * @param request The certificate request.
     */
    Certificate* emitCertificate(CertificateRequest request);

    /**
     * @brief Getter for the certificate authority's certificate.
     */
    const Certificate getCertificate();

    /**
     * @brief Saves the certificate authority's certificate to a p12 file.
     */
    bool save();
};


#endif // !CERTIFICATE_AUTHORITY_H