#ifndef SESSION_MANAGER_H
#define SESSION_MANAGER_H

#include <vector>
#include <string>
#include "session.h"


using namespace std;


/**
 * @brief Responsible for managing the sessions of the application.
 *
 */
class SessionManager
{
private:
    vector<Session*> sessions;
    Session* currentSession;

public:
    SessionManager();

    ~SessionManager();

    /**
     * @brief Creates a new session.
     * 
     * @param sessionName The name of the session.
     * @param filename The name of the file to be signed.
     * @param password The password of the session.
     * @param numOfSigners The number of signers of the session.
     * @param admin The session's admin. By default, the creator of the session.
     * @param messageDigest
     */
    bool createSession(
        string sessionName,
        string filename,
        string password,
        unsigned int numOfSigners,
        User* admin,
        MessageDigest* messageDigest);

    /**
     * @brief Enters a session.
     * 
     * @param sessionName The name of the session.
     * @param password The password of the session.
     * 
     * @return True if enter attempt was successful, false otherwise.
     */
    bool enterSession(string sessionName, string password);

    /**
     * @brief Leaves the current session.
     * 
     * @return True if leave attempt was successful, false otherwise.
     */
    bool leaveSession();

    /**
     * @brief Signs the file of the current session.
     * 
     * @param signer The signer object.
     * @param currentUser The current user.
     * 
     * @return True if sign attempt was successful, false otherwise.
     */
    bool sign(Signer* signer, User* currentUser);

    /**
     * @brief Verifies the signatres in the current session's file.
     * 
     * @param signer The signer object.
     * @param authCertificate The Certificate Authority's certificate.
     * 
     * @return True if all needed signatures are present and valid, false
     * otherwise.
     */
    bool verify(Signer* signer, Certificate authCertificate);

    /**
     * @brief Logs out the current user.
     */
    void logOut();

    /**
     * @brief Getter for all the registered sessions' names.
     */
    vector<string> getSessionsNames();

    /**
     * @brief Getter for the current session's name.
     */
    string getCurrentSessionName();

};

#endif // !SESSION_MANAGER_H