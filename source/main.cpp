#include "headers/Application.hpp"

#define WIN_WIDTH 1080
#define WIN_HEIGHT 720
#define WIN_NAME "Fast!"

int main(int, char**) {
    Application application(
        WIN_WIDTH,
        WIN_HEIGHT,
        WIN_NAME
    );
    return 0;
}