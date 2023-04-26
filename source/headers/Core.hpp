#pragma once

#include <iostream>

#define INT_16 short int
#define UINT_16 unsigned short int
#define INT_32 int
#define UINT_32 unsigned int
#define INT_64 long long int
#define UINT_64 unsigned long long int

enum WindowStatus {
    WINDOW_RUNNING,
    WINDOW_PAUSED,
    WINDOW_CLOSED
};

namespace Utils {
    void print_sdl_error_message(std::string);
    void print_debug_message(std::string);
};