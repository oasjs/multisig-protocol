#include <iostream>
#include "session_manager.h"

using namespace std;


SessionManager::SessionManager()
{
    currentSession = nullptr;
}

SessionManager::~SessionManager()
{
    for (auto session : sessions) {
        delete session;
    }
}

bool SessionManager::createSession(
    string sessionName,
    string filename,
    string password,
    unsigned int numOfSigners,
    User* admin,
    MessageDigest* messageDigest)
    {
    if (currentSession != nullptr) {
        return false;
    }

    for (auto session : sessions) {
        if (session->getName() == sessionName) {
            cout << "Session with name " << sessionName <<
                                                    " already exists" << endl;
            return false;
        }
    }

    Session* session = new Session(
        sessionName, filename, password, numOfSigners, admin);

    if (!session->setUp(messageDigest)) {
        return false;
    }

    sessions.push_back(session);
    return true;
}

bool SessionManager::enterSession(string sessionName, string password)
{
    for (auto session : sessions) {
        if (session->getName() == sessionName) {
            if (session->authenticate(password)) {
                currentSession = session;
                return true;
            }
            else {
                return false;
            }
        }
    }

    cout << "Session with name " << sessionName << " does not exist" << endl;
    return false;
}

bool SessionManager::sign(
    Signer* signer, User* currentUser)
{
    if (currentSession == nullptr) {
        cout << "You must enter a session before signing" << endl;
        return false;
    }
    Certificate* cert = currentUser->getCertificate();
    if (cert == nullptr) {
        cout << "You must have a certificate to sign" << endl;
        return false;
    }
    return currentSession->sign(signer, currentUser);
}

bool SessionManager::verify(
    Signer* signer, Certificate authCertificate)
{
    if (currentSession == nullptr) {
        cout << "You must enter a session before verifying" << endl;
        return false;
    }
    return currentSession->verify(signer, authCertificate);
}

bool SessionManager::leaveSession()
{
    if (currentSession == nullptr) {
        return false;
    }
    currentSession = nullptr;
    return true;
}

void SessionManager::logOut()
{
    return;
}

vector<string> SessionManager::getSessionsNames()
{
    vector<string> names;
    for (auto session : sessions) {
        names.push_back(session->getName());
    }
    return names;
}

string SessionManager::getCurrentSessionName()
{
    if (currentSession == nullptr) {
        return "";
    }
    return currentSession->getName();
}
