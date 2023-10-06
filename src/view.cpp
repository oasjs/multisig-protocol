#include <iostream>
#include <unistd.h>
#include "view.h"
#include "enums.h"


using namespace std;

View::View() {}

View::~View() {}

void View::clear()
{
    system("clear");
}

void View::printWelcome()
{
    clear();
    cout << "Welcome to MultiSign!" << endl << endl;
    cout <<
        "Are you hoping to seal an agreement that will save the world? " <<
        "Then you came to the right application!" << endl;
}

void View::printMainMenu()
{
    cout << endl;
    cout << "Main Menu" << endl;
    cout << endl;
    cout << "1 - Register" << endl;
    cout << "2 - Login" << endl;
    cout << "3 - Exit" << endl;
    cout << "Option: ";
}

void View::printRegisterMenu()
{
    cout << endl;
    cout << "Register Menu" << endl;
    cout << endl;
    cout << "1 - Register" << endl;
    cout << "2 - Back" << endl;
    cout << "Option: ";
}

void View::printLoginMenu()
{
    cout << endl;
    cout << "Login Menu" << endl;
    cout << endl;
    cout << "1 - Login" << endl;
    cout << "2 - Back" << endl;
    cout << "Option: ";
}

void View::printSessionManagerMenu(vector<string> sessionNames)
{
    cout << endl;
    cout << "Session Manager" << endl;
    cout << "Available sessions:";
    for (auto sessionName : sessionNames)
    {
        cout << "   " << sessionName;
    }
    cout << endl;
    cout << "1 - Create Session" << endl;
    cout << "2 - Enter Session" << endl;
    cout << "3 - Log out" << endl;
    cout << "Option: ";
}

void View::printSessionMenu(string sessionName)
{
    cout << endl;
    cout << "Session: " << sessionName << endl;
    cout << endl;
    cout << "1 - Sign" << endl;
    cout << "2 - Verify" << endl;
    cout << "3 - Leave session" << endl;
    cout << "Option: ";
}