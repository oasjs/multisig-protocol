#ifndef REGISTRY_H
#define REGISTRY_H

#include <string>
#include <map>
#include "user.h"

using namespace std;

/**
 * @brief Represents the application's registry for users.
 * 
 * @details The registry is responsible for managing the users of the
 * application, including registering, logging in and logging out.
 */
class Registry
{
private:
    map<string, User*> users;

public:
    Registry();

    ~Registry();

    /**
     * @brief Registers a new user.
     */
    User* registerUser(pair<string, string> userCredentials);

    /**
     * @brief Logs in a user.
     */
    User* logIn(pair<string, string> userCredentials);

    /**
     * @brief Looks for a user in the registry.
     * 
     * @return True if the user is found, false otherwise.
     */
    bool findUser(string userName);

    /**
     * @brief Saves the users' certificates to p12 files.
     */
    void saveUsers();

    /**
     * @brief Loads the users' certificates from p12 files.
     */
    void loadUserNames();

    /**
     * @brief Loads a user's certificate from a p12 file.
     */
    bool loadUser(string userName, string password);

};

#endif // !REGISTRY_H