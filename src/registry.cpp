#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <libcryptosec/Pkcs12.h>
#include "registry.h"

extern "C" {
    #include <openssl/pkcs12.h>
    #include <openssl/pem.h>
    #include <openssl/err.h>
}

using namespace std;

Registry::Registry() {}

Registry::~Registry()
{
    for (auto it = users.begin(); it != users.end(); it++)
    {
        if (it->second != nullptr)
            delete it->second;
    }
}

User* Registry::registerUser(pair<string, string> userCredentials)
{
    if (findUser(userCredentials.first))
    {
        return nullptr;
    }
    User* user = new User(userCredentials);
    users.insert(make_pair(userCredentials.first, user));
    return user;
}

User* Registry::logIn(pair<string, string> userCredentials)
{
    if (!findUser(userCredentials.first))
    {
        return nullptr;
    }
    if (users[userCredentials.first] == nullptr)
    {
        bool loadedUser = loadUser(
            userCredentials.first, userCredentials.second);
        if (!loadedUser)
        {
            return nullptr;
        }
    }
    User* user = users[userCredentials.first];
    if (!user->authenticate(userCredentials.second))
    {
        return nullptr;
    }
    return user;
}


bool Registry::findUser(string userName)
{
    return users.find(userName) != users.end();
}

void Registry::saveUsers()
{
    for (auto u : users) {
        if (u.second == nullptr)
            continue;
        if (!u.second->save())
            cout << "Error saving user " << u.first << endl;
    }
}

void Registry::loadUserNames()
{
    const char* directory_path = USERS_PATH.c_str();

    DIR* directory = opendir(directory_path);
    if (directory) {
        struct dirent* entry;
        while ((entry = readdir(directory))) {
            if (entry->d_type == DT_REG) {
                string filename = entry->d_name;
                string userName = filename.substr(0, filename.find(".p12"));
                users.insert(make_pair(userName, nullptr));
            }
        }
        closedir(directory);
    } else {
        cerr << "Unable to open the directory." << endl;
    }
}

bool Registry::loadUser(string userName, string password)
{
    FILE *file;
    PKCS12 *p12;
    string filename = USERS_PATH + userName + ".p12";

    if (!(file = fopen(filename.c_str(), "r"))) {
        cerr << "Unable to open file " << filename << endl;
        return false;
    }

    p12 = d2i_PKCS12_fp(file, NULL);
    if (!p12) {
        cerr << "Unable to read file " << filename << endl;
        return false;
    }
    fclose(file);

    Pkcs12 pkcs12 = Pkcs12(p12);
    PrivateKey* privKey = pkcs12.getPrivKey(password);
    Certificate* cert = pkcs12.getCertificate(password);

    User* user = new User(userName, password, cert, privKey);
    users[userName] = user;

    return true;
}