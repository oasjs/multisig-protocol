#ifndef CONTROL_H
#define CONTROL_H

#include <iostream>
#include <vector>
#include <string>
#include "view.h"

using namespace std;

/**
 * @brief The control class is responsible for capturing user input and
 * responding to it.
 */
class Control
{
private:

public:
    Control();

    ~Control();

    /**
     * @brief Captures user input.
     * 
     * @return The user input.
     */
    const int waitInput();

    /**
     * @brief Requests the credentials when registering a new user.
     * 
     * @return A pair containing the username and password respectively.
     */
    const pair<string, string> requestRegister();

    /**
     * @brief Requests the credentials when logging in a user.
     * 
     * @return A pair containing the username and password respectively.
     */
    const pair<string, string> requestLogin();

    /**
     * @brief Structure for encapsulating the session creation parameters.
     */
    struct SessionParams
    {
        string sessionName;
        string password;
        string filename;
        unsigned int numOfSigners;
    };

    /**
     * @brief Requests the session creation parameters.
     * 
     * @return The session creation parameters.
     */
    const SessionParams requestSessionCreationParams();

    /**
     * @brief Requests the session enter credentials.
     * 
     * @return A pair containing the session name and password respectively.
     */
    const pair<string, string> requestSessionCredentials();

    /**
     * @brief Responds to a registration attempt.
     */
    static void respondRegister(bool registered);

    /**
     * @brief Responds to a login attempt.
     */
    static void respondLogin(bool loggedIn);

    /**
     * @brief Responds to a session creation attempt.
     */
    static void respondSessionCreation(bool sessionCreated);

    /**
     * @brief Responds to a session enter attempt.
     */
    static void respondSessionEnter(bool sessionEntered);

    /**
     * @brief Responds to a document signing attempt.
     */
    static void respondSigning(bool hasSigned);

    /**
     * @brief Responds to a document verification attempt.
     */
    static void respondVerification(bool verified);

    /**
     * @brief Requests for the user to press enter to continue the application's
     * flow.
     */
    static void requestContinue();

};

#endif // !CONTROL_H