#ifndef APPLICATION_H
#define APPLICATION_H

#include <libcryptosec/Signer.h>
#include <libcryptosec/MessageDigest.h>

#include "view.h"
#include "control.h"
#include "session_manager.h"
#include "registry.h"
#include "certificate_authority.h"

using namespace std;


/**
 * @brief The application's main class. It is responsible for the application's
 * flow.
 *
 * @details The application's flow is divided into menus. Each menu has its own
 * handler. The application's flow is controlled by the currentMenu variable.
 */
class Application
{
private:
    View view;
    Control control;
    Registry registry;
    SessionManager sessionManager;

    CertificateAuthority* certAuth;
    MessageDigest* messageDigest;
    Signer* signer;

    User* currentUser;
    int currentMenu;
    bool running;

    /**
     * @brief Process user input caputred by the control.
     */
    void processInput();

    /**
     * @brief Handle the main menu options.
     */
    void handleMainMenu();

    /**
     * @brief Handle the register menu options.
     */
    void handleRegister();

    /**
     * @brief Handle the login menu options.
     */
    void handleLogin();

    /**
     * @brief Handle the session manager menu options.
     */
    void handleSessionManager();

    /**
     * @brief Handle the session menu options.
     */
    void handleSession();

    /**
     * @brief Loads the certificate authority's from a p12 file, if exists.
     */
    bool loadCertificateAuthority();

    /**
     * @brief Exits the application.
     */
    void exit();

public:
    Application();

    ~Application();

    /**
     * @brief Starts the application.
     */
    void start();

};


#endif // !APPLICATION_H