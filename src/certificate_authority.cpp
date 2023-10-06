#include <iostream>
#include <fstream>
#include <libcryptosec/Pkcs12Builder.h>
#include "constants.h"
#include "certificate_authority.h"


using namespace std;

CertificateAuthority::CertificateAuthority()
{
    RSAKeyPair keyPair = RSAKeyPair(KEY_SIZE);
    privateKey = keyPair.getPrivateKey();
    publicKey = keyPair.getPublicKey();
}

CertificateAuthority::CertificateAuthority(Pkcs12* pkcs12)
{
    privateKey = pkcs12->getPrivKey(password);
    authCertificate = pkcs12->getCertificate(password);
    publicKey = authCertificate->getPublicKey();
}

CertificateAuthority::~CertificateAuthority()
{
    if (authCertificate != nullptr) {
        delete authCertificate;
    }
    if (privateKey != nullptr) {
        delete privateKey;
    }
}

void CertificateAuthority::emitOwnCertificate()
{
    RDNSequence authCredentials;
    authCredentials.addEntry(RDNSequence::COUNTRY, "BR");
    authCredentials.addEntry(RDNSequence::STATE_OR_PROVINCE, "SC");
    authCredentials.addEntry(RDNSequence::LOCALITY, "FLORIANOPOLIS");
    authCredentials.addEntry(RDNSequence::ORGANIZATION, "NOTLABSEC");
    authCredentials.addEntry(RDNSequence::ORGANIZATION_UNIT, "PKINOTLABSEC");
    authCredentials.addEntry(RDNSequence::COMMON_NAME, name);
    authCredentials.addEntry(RDNSequence::EMAIL, "fake@mail.com");

    CertificateBuilder certBuilder = CertificateBuilder();
    certBuilder.setIssuer(authCredentials);
    certBuilder.setSubject(authCredentials);
    certBuilder.setPublicKey(*publicKey);
    certBuilder.setSerialNumber(1);
    authCertificate = certBuilder.sign(*privateKey, HASH_ALGORITHM);
}

Certificate* CertificateAuthority::emitCertificate(CertificateRequest request)
{
    CertificateBuilder certBuilder = CertificateBuilder(request);
    RDNSequence issuer = authCertificate->getIssuer();
    certBuilder.setIssuer(issuer);

    return certBuilder.sign(*privateKey, HASH_ALGORITHM);
}

const Certificate CertificateAuthority::getCertificate()
{
    return *authCertificate;
}

bool CertificateAuthority::save()
{
    if (authCertificate == nullptr)
        return false;

    string filename = CERT_AUTH_PATH + name + ".p12";
    ofstream file(filename, ios::out | ios::trunc);
    if (file.is_open()) {

        Pkcs12Builder builder;
        builder.setKeyAndCertificate(
            privateKey, authCertificate, name);

        Pkcs12* pkcs12 = builder.doFinal(password);
        ByteArray pkcs12Data = pkcs12->getDerEncoded();
        istringstream* pkcs12Stream = pkcs12Data.toStream();

        file << pkcs12Stream->rdbuf();
        file.close();

        delete pkcs12;
        delete pkcs12Stream;
        return true;
    } else {
        cout << "Failed to open output file." << endl;
        return false;
    }

    return true;
}