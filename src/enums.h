#ifndef ENUMS_H
#define ENUMS_H

namespace menus
{
/**
 * @brief Enum for the menus of the application.
 */
enum Menu {
    MAIN = 1,
    REGISTER,
    LOGIN,
    SESSION_MANAGER,
    SESSION
};

} // namespace menus

namespace mainMenu 
{
/**
 * @brief Enum for the main menu options.
 */
enum MainMenu {
    REGISTER = 1,
    LOGIN,
    EXIT,
};

} // namespace mainMenu


namespace registerMenu
{
/**
 * @brief Enum for the register menu options.
 */
enum RegisterMenu {
    REGISTER = 1,
    BACK,
};

} // namespace registerMenu

namespace loginMenu
{
/**
 * @brief Enum for the login menu options.
 */
enum LoginMenu {
    LOGIN = 1,
    BACK,
};

} // namespace loginMenu

namespace sessionManager
{
/**
 * @brief Enum for the session menu options.
 */

enum SessionManagerMenu {
    CREATE_SESSION = 1,
    ENTER_SESSION,
    LOGOUT
};

} // namespace registerMenu


namespace sessionMenu
{
/**
 * @brief Enum for the session menu options.
 */
enum SessionMenu {
    SIGN = 1,
    VERIFY,
    LEAVE_SESSION
};

} // namespace sessionMenu


#endif // !ENUMS_H