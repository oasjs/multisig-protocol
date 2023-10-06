#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdio>
#include "session.h"


using namespace std;


Session::Session(
    string sessionName,
    string filename,
    string password,
    unsigned int numOfSigners,
    User* admin) :
        sessionName(sessionName),
        filename(filename),
        password(password),
        numOfSigners(numOfSigners),
        isClosed(false) {}

Session::~Session()
{
}

bool Session::setUp(MessageDigest* messageDigest)
{
    if (!readPDF()) {
        return false;
    }
    hashTextContent(messageDigest);
    return true;
}

bool Session::readPDF()
{
    string outputFilePath = TMP_PATH + sessionName + ".txt";

    string command =
                "pdftotext " + PDF_PATH + filename + ".pdf " + outputFilePath;
    int status = system(command.c_str());

    if (status == 0) {
        cout << "Text extraction successful." << endl;
    } else {
        cout << "Text extraction failed." << endl;
        return false;
    }

    ifstream outputFile(outputFilePath);
    if (outputFile.is_open()) {
        string line;
        while (getline(outputFile, line)) {
            textContent += line + "\n";
        }
        outputFile.close();

    } else {
        cout << "Failed to open output file." << endl;
        return false;
    }

    return true;
}

void Session::hashTextContent(MessageDigest* messageDigest)
{
    messageDigest->init(HASH_ALGORITHM);
    messageDigest->update(textContent);
    hashedText = messageDigest->doFinal();
}

bool Session::sign(Signer* signer, User* currentUser)
{
    if (signatures.size() >= numOfSigners) {
        cout << "Maximum number of signatures reached" << endl;
        return false;
    }
    ByteArray signature = currentUser->sign(signer, hashedText);
    signatures[currentUser] = signature;
    return true;
}

bool Session::verify(Signer* signer, Certificate authCertificate)
{
    PublicKey authPublicKey = *authCertificate.getPublicKey();

    for (auto s : signatures) {
        User* user = s.first;
        ByteArray signature = s.second;
        Certificate* userCertificate = user->getCertificate();

        if (!userCertificate->verify(authPublicKey))
        {
            cout << "User certificate verification failed" << endl;
            return false;
        }
        PublicKey userPublicKey = *userCertificate->getPublicKey();
        if (!signer->verify(
            userPublicKey, signature, hashedText, HASH_ALGORITHM))
        {
            cout << "Signature verification failed" << endl;
            return false;
        }
        cout    << "Signature from operator " << user->getName()
                << " verified successfully." << endl;
    }

    if (signatures.size() < numOfSigners) {
        cout << "Not enough signatures" << endl;
        return false;
    }
    return true;
}

bool Session::authenticate(string password)
{
    return this->password == password;
}

string Session::getName()
{
    return sessionName;
}
