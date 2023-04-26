#include <iostream>
#include <time.h>
#include <SDL.h>

#include "../headers/Core.hpp"

void Utils::print_sdl_error_message(std::string message) {
    std::cout << "[___ERROR___]\n";
    std::cout << "Message: " << message << '\n';
    std::cout << "SDL_GetError(): " << SDL_GetError() << '\n';
    std::cout << "-------------\n";
}

void Utils::print_debug_message(std::string message) {
    std::cout << "[DEBUG]: " << message << '\n';
}

float Utils::hire_time_in_seconds() {
    float t = SDL_GetTicks();
    t *= .001f;
    return t;
}

INT_32 Utils::random_number(INT_32 from, INT_32 to) {
    srand(time(NULL));
    return rand() % (to - from) + from;
}