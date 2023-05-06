/*
    Main file of the project.
*/

#include "headers/Application.hpp"
#include "headers/Core.hpp"

int main(int, char**) {
    // Set the debug mode
    Utils::set_debug_mode(true);

    // Set the crash mode
    Utils::set_crash(true);

    // Create the application.
    Application application(
        WIN_WIDTH,
        WIN_HEIGHT,
        WIN_NAME
    );
    return 0;
}