#include <iostream>
#include <string>
#include <limits>
#include <unistd.h>
#include "control.h"

using namespace std;

Control::Control() {}

Control::~Control() {}

const int Control::waitInput()
{
    string input;
    int option;

    cin >> input;

    try
    {
        option = stoi(input);
    }
    catch (const std::exception &e)
    {
        option = -1;
    }

    return option;
}

void Control::requestContinue()
{
    cout << endl << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

const pair<string, string> Control::requestRegister()
{
    string username;
    string password;

    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    cin.ignore();

    return make_pair(username, password);
}

const pair<string, string> Control::requestLogin()
{
    string username;
    string password;

    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    cin.ignore();

    return make_pair(username, password);
}

const Control::SessionParams Control::requestSessionCreationParams()
{
    SessionParams info;

    cout << "Session name: ";
    cin >> info.sessionName;
    cout << "Password: ";
    cin >> info.password;
    cout << "Filename: ";
    cin >> info.filename;
    cout << "Number of signers: ";
    cin >> info.numOfSigners;

    cin.ignore();

    return info;
}

const pair<string, string> Control::requestSessionCredentials()
{
    string sessionName;
    string password;

    cout << "Session name: ";
    cin >> sessionName;
    cout << "Password: ";
    cin >> password;

    cin.ignore();

    return make_pair(sessionName, password);
}

void Control::respondRegister(bool registered)
{
    if (registered)
    {
        cout << "Registered successfully!" << endl;
    }
    else
    {
        cout << "Username already in use!" << endl;
    }
    requestContinue();
}

void Control::respondLogin(bool loggedIn)
{
    if (loggedIn)
    {
        cout << "Logged in successfully!" << endl;
    }
    else
    {
        cout << "Invalid credentials!" << endl;
    }
    requestContinue();
}

void Control::respondSessionCreation(bool sessionCreated)
{
    if (sessionCreated)
    {
        cout << "Session created successfully!" << endl;
    }
    else
    {
        cout << "Failed to create session." << endl;
        cout << "Check if there is already a session with the"
                "same name or if the PDF file exists in the pdf folder."
                << endl;
    }
    requestContinue();
}

void Control::respondSessionEnter(bool sessionEntered)
{
    if (sessionEntered)
    {
        cout << "Entered session successfully!" << endl;
    }
    else
    {
        cout << "Invalid session credentials." << endl;
    }
    requestContinue();
}

void Control::respondSigning(bool hasSigned)
{
    if (hasSigned)
    {
        cout << "Signed successfully!" << endl;
    }
    else
    {
        cout << "Failed to sign." << endl;
    }
    cin.ignore();
    requestContinue();
}

void Control::respondVerification(bool verified)
{
    if (verified)
    {
        cout << "All signatures present and verified successfully!" << endl;
        cout << endl;
        cout << "The agreement is valid. "
                "Congratulations, you have saved the world!" << endl;
    }
    else
    {
        cout << "Failed to verify." << endl;
    }
    cin.ignore();
    requestContinue();
}