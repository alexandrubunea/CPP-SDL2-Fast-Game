#include <iostream>
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