#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/**
 * @brief The view class is responsible for printing the application's menus.
 */
class View
{
private:

public:
    View();

    ~View();

    /**
     * @brief Prints the welcome message.
     */
    static void printWelcome();

    /**
     * @brief Prints the main menu.
     */
    static void printMainMenu();

    /**
     * @brief Prints the register menu.
     */
    static void printRegisterMenu();

    /**
     * @brief Prints the login menu.
     */
    static void printLoginMenu();

    /**
     * @brief Prints the session manager menu.
     * 
     * @param sessionsNames The names of the sessions to be printed.
     */
    static void printSessionManagerMenu(vector<string> sessionsNames);

    /**
     * @brief Prints the session menu.
     * 
     * @param sessionName The name of the session to be printed.
     */
    static void printSessionMenu(string sessionName);

    /**
     * @brief Clears the terminal.
     */
    static void clear();
};

#endif // !VIEW_H
