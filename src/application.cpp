
#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <libcryptosec/Pkcs12.h>
#include "application.h"
#include "enums.h"

extern "C" {
    #include <openssl/pkcs12.h>
    #include <openssl/pem.h>
    #include <openssl/err.h>
}

Application::Application() {
    messageDigest = new MessageDigest();
    signer = new Signer();

    // Warning: DO NOT REMOVE THE FOLLOWING LINES!
    messageDigest->loadMessageDigestAlgorithms();
    messageDigest->init(HASH_ALGORITHM);
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();
}

Application::~Application() {
    delete certAuth;
    delete messageDigest;
    delete signer;
}

void Application::start()
{
    currentMenu = menus::MAIN;
    currentUser = nullptr;
    running = true;

    if (!loadCertificateAuthority())
    {
        certAuth = new CertificateAuthority();
        certAuth->emitOwnCertificate();
    }
    registry.loadUserNames();

    view.printWelcome();
    control.requestContinue();
    while (running)
    {
        processInput();
    }
}

void Application::exit()
{
    running = false;
}

void Application::processInput()
{
    view.clear();
    switch (currentMenu)
    {
        case menus::MAIN:
        {
            handleMainMenu();
            break;
        }
        case menus::REGISTER:
        {
            handleRegister();
            break;
        }
        case menus::LOGIN:
        {
            handleLogin();
            break;
        }
        case menus::SESSION_MANAGER:
        {
            handleSessionManager();
            break;
        }
        case menus::SESSION:
        {
            handleSession();
            break;
        }
        default:
        {
            cout << "Invalid menu" << endl;
            sleep(1);
            break;
        }
    }
}

void Application::handleMainMenu()
{
    view.printMainMenu();
    int option = control.waitInput();

    switch (option)
    {
        case mainMenu::REGISTER:
        {
            currentMenu = menus::REGISTER;
            break;
        }
        case mainMenu::LOGIN:
        {
            currentMenu = menus::LOGIN;
            break;
        }
        case mainMenu::EXIT:
        {
            cout << "Saving certificate authority..." << endl;
            certAuth->save();
            cout << "Saving users..." << endl;
            registry.saveUsers();
            cout << "Exiting..." << endl;
            exit();
            break;
        }
        default:
        {
            cout << "Invalid option" << endl;
            sleep(1);
            break;
        } 
    }
}

void Application::handleRegister()
{
    view.printRegisterMenu();
    int option = control.waitInput();

    switch (option)
    {
        case registerMenu::REGISTER:
        {
            pair<string, string> credentials = control.requestRegister();
            User* user = registry.registerUser(credentials);
            bool isRegistered = user != nullptr;

            if (isRegistered)
            {
                Certificate* cert =
                            certAuth->emitCertificate(user->issueRequest());
                user->setCertificate(cert);
                currentMenu = menus::MAIN;
            }
            control.respondRegister(isRegistered);
            break;
        }
        case registerMenu::BACK:
        {
            currentMenu = menus::MAIN;
            break;
        }
        default:
        {
            cout << "Invalid option" << endl;
            sleep(1);
            break;
        }
    }
}

void Application::handleLogin()
{
    view.printLoginMenu();
    int option = control.waitInput();

    switch (option)
    {
        case loginMenu::LOGIN:
        {
            pair<string, string> credentials = control.requestLogin();
            User* user = registry.logIn(credentials);
            bool isLoggedIn = user != nullptr;

            control.respondLogin(isLoggedIn);
            if (isLoggedIn)
            {
                currentUser = user;
                currentMenu = menus::SESSION_MANAGER;
            }
            break;
        }
        case loginMenu::BACK:
        {
            currentMenu = menus::MAIN;
            break;
        }
        default:
        {
            cout << "Invalid option" << endl;
            sleep(1);
            break;
        }
    }
}

void Application::handleSessionManager()
{
    view.printSessionManagerMenu(sessionManager.getSessionsNames());
    int option = control.waitInput();

    switch (option)
    {
        case sessionManager::CREATE_SESSION:
        {
            Control::SessionParams info =
                                        control.requestSessionCreationParams();
            bool sessionCreated = sessionManager.createSession(
                info.sessionName, info.filename, info.password,
                info.numOfSigners, currentUser, messageDigest);

            control.respondSessionCreation(sessionCreated);
            break;
        }
        case sessionManager::ENTER_SESSION:
        {
            pair<string, string> credentials =
                                            control.requestSessionCredentials();
            bool enteredSession = sessionManager.enterSession(
                                        credentials.first, credentials.second);
            if (enteredSession)
            {
                currentMenu = menus::SESSION;
            }

            control.respondSessionEnter(enteredSession);
            break;
        }
        case sessionManager::LOGOUT:
        {
            currentMenu = menus::MAIN;
            currentUser = nullptr;
            break;
        }
        default:
        {
            cout << "Invalid option" << endl;
            break;
        }
    }
}

void Application::handleSession()
{
    view.printSessionMenu(sessionManager.getCurrentSessionName());
    int option = control.waitInput();

    switch (option)
    {
        case sessionMenu::SIGN:
        {
            bool hasSigned = sessionManager.sign(signer, currentUser);
            control.respondSigning(hasSigned);
            break;
        }
        case sessionMenu::VERIFY:
        {
            Certificate authCertificate = certAuth->getCertificate();
            bool verified = sessionManager.verify(signer, authCertificate);

            control.respondVerification(verified);
            break;
        }
        case sessionMenu::LEAVE_SESSION:
        {
            currentMenu = menus::SESSION_MANAGER;
            break;
        }
        default:
        {
            cout << "Invalid option" << endl;
            break;
        }
    }
}

bool Application::loadCertificateAuthority()
{
    const char* directory_path = CERT_AUTH_PATH.c_str();
    bool loaded = false;

    DIR* directory = opendir(directory_path);
    if (directory) {
        struct dirent* entry;
        while ((entry = readdir(directory))) {
            if (entry->d_type == DT_REG) {
                FILE *file;
                PKCS12 *p12;

                string filename = CERT_AUTH_PATH + string(entry->d_name);

                if (!(file = fopen(filename.c_str(), "r"))) {
                    cerr << "Unable to open file " << entry->d_name << endl;
                    continue;
                }

                p12 = d2i_PKCS12_fp(file, NULL);
                if (!p12) {
                    cerr << "Unable to read file " << entry->d_name << endl;
                    continue;
                }
                fclose(file);

                Pkcs12* pkcs12 = new Pkcs12(p12);
                certAuth = new CertificateAuthority(pkcs12);
                delete pkcs12;

                loaded = true;
            }
        }
    }
    closedir(directory);
    return loaded;
}