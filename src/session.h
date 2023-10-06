#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <vector>
#include <map>
#include <libcryptosec/Signer.h>
#include <libcryptosec/MessageDigest.h>
#include "user.h"

using namespace std;

/**
 * @brief Represents a session of the application.
 * 
 * @details A session is composed by a file to be signed and a group of
 * signatures.
 */
class Session
{
private:
    string sessionName;
    string filename;
    string password;
    unsigned int numOfSigners;

    string textContent;
    ByteArray hashedText;
    map<User*, ByteArray> signatures;

    bool isClosed;

    /**
     * @brief Reads the PDF file to be signed and stores its text content.
     * 
     * @return True if the file was read successfully, false otherwise.
     */
    bool readPDF();

    /**
     * @brief Hashes the text content of the file to be signed and stores the
     * hash result.
     */
    void hashTextContent(MessageDigest* messageDigest);

public:
    Session(
        string sessionName,
        string filename,
        string password,
        unsigned int numOfSigners,
        User* admin);

    ~Session();

    /**
     * @brief Calls the readPDF() and hashTextContent() methods.
     * 
     * @return True if the setup was successful, false otherwise.
     */
    bool setUp(MessageDigest* messageDigest);

    /**
     * @brief Signs the file to be signed.
     * 
     * @param signer The signer object.
     * @param currentUser The current user.
     * 
     * @return True if the sign attempt was successful, false otherwise.
     */
    bool sign(Signer* signer, User* currentUser);

    /**
     * @brief Verifies the signatures of the file to be signed.
     * 
     * @param signer The signer object.
     * @param authCertificate The Certificate Authority's certificate.
     * 
     * @return True if the verification attempt was successful, false otherwise.
     */
    bool verify(Signer* signer, Certificate authCertificate);

    /**
     * @brief Authenticates an enter attempt to the session.
     * 
     * @param password The password of the session.
     * 
     * @return True if the authentication attempt was successful, false
     * otherwise.
     */
    bool authenticate(string password);

    /**
     * @brief Getter for the session's name.
     */
    string getName();
};

#endif // !SESSION_H