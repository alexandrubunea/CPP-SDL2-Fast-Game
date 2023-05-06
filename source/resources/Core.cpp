#include <random>
#include <SDL.h>
#include <SDL_image.h>

#include "../headers/Core.hpp"

namespace Utils {
    std::ofstream log_file = std::ofstream("log.txt");
    bool CRASH = false;
    bool DEBUG_MODE = false;
}

void Utils::print_sdl_error_message(std::string message) {
    log_file << "[___ERROR___]\n";
    log_file << "Message: " << message << '\n';
    log_file << "SDL_GetError(): " << SDL_GetError() << '\n';
    log_file << "-------------\n";
}

void Utils::print_sdl_image_error_message(std::string message) {
    log_file << "[___ERROR___]\n";
    log_file << "Message: " << message << '\n';
    log_file << "IMG_GetError(): " << IMG_GetError() << '\n';
    log_file << "-------------\n";
}

void Utils::set_crash(bool crash) {
    CRASH = crash;
}

void Utils::set_debug_mode(bool debug_mode) {
    DEBUG_MODE = debug_mode;
}

void Utils::print_debug_message(std::string message) {
    if(!DEBUG_MODE) 
        return;
    log_file << "[DEBUG]: " << message << '\n';
}

float Utils::hire_time_in_seconds() {
    // Get the current time in seconds
    float t = SDL_GetTicks();
    t *= .001f;
    return t;
}

INT_32 Utils::random_number(INT_32 from, INT_32 to) {
    /*
        We use the Mersenne Twister 19937 generator
        We use the random device to seed the generator
        We use the uniform distribution to generate a random number

        Resources:
        https://en.cppreference.com/w/cpp/numeric/random
        https://en.cppreference.com/w/cpp/numeric/random/random_device
        https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine
        https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
    */
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<INT_32> dist(from, to);

    return dist(mt);
}