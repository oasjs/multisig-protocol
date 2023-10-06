#include <iostream>
#include <fstream>
#include <libcryptosec/Pkcs12Builder.h>
#include <istream>
#include "user.h"
#include "constants.h"


extern "C" {
    #include <openssl/pkcs12.h>
    #include <openssl/pem.h>
    #include <openssl/err.h>
}

using namespace std;


User::User(pair<string, string> userCredentials) :
    name(userCredentials.first),
    password(userCredentials.second),
    certificate(nullptr)
{
    subjectInfo.addEntry(RDNSequence::COMMON_NAME, name);
    RSAKeyPair keyPair = RSAKeyPair(KEY_SIZE);
    privateKey = keyPair.getPrivateKey();
    publicKey = keyPair.getPublicKey();
}

User::User(string name,
    string password,
    Certificate* certificate,
    PrivateKey* privateKey) :
        name(name),
        password(password),
        certificate(certificate),
        privateKey(privateKey)
{
    subjectInfo.addEntry(RDNSequence::COMMON_NAME, name);
    publicKey = certificate->getPublicKey();
}

User::~User() {
    if (certificate != nullptr)
        delete certificate;
    if (privateKey != nullptr)
        delete privateKey;
}

void User::setCertificate(Certificate* certificate)
{
    if (this->certificate == nullptr)
        this->certificate = certificate;
}

bool User::authenticate(string password)
{
    return this->password == password;
}

ByteArray User::sign(Signer* signer, ByteArray& hash)
{
    return signer->sign(*privateKey, hash, HASH_ALGORITHM);
}

CertificateRequest User::issueRequest()
{
    CertificateRequest request;
    request.setPublicKey(*publicKey);
    request.setSubject(subjectInfo);

    return request;
}

Certificate* User::getCertificate()
{
    return certificate;
}

const string User::getName()
{
    return name;
}

bool User::save()
{
    if (certificate == nullptr)
        return false;

    string filename = USERS_PATH + name + ".p12";
    ofstream file(filename, ios::out | ios::trunc);
    if (file.is_open()) {
        Pkcs12Builder builder;
        builder.setKeyAndCertificate(
            privateKey, certificate, name);

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
