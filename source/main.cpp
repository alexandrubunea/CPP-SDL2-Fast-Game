/*
    Main file of the project.
*/

#include "headers/Application.hpp"
#include "headers/Core.hpp"

int main(int, char**) {
    // Create the application.
    Application application(
        WIN_WIDTH,
        WIN_HEIGHT,
        WIN_NAME
    );
    return 0;
}