#pragma once

#include <iostream>

#define INT_16 short int
#define UINT_16 unsigned short int
#define INT_32 int
#define UINT_32 unsigned int
#define INT_64 long long int
#define UINT_64 unsigned long long int

#define PLAYER_WIDTH 25
#define PLAYER_HEIGHT 50
#define PLAYER_X 100
#define PLAYER_Y 100

enum WindowStatus {
    WINDOW_RUNNING,
    WINDOW_PAUSED,
    WINDOW_CLOSED
};

namespace Utils {
    struct Vector2D {
        float x, y;
        Vector2D(float X=0, float Y=0) :
        x(X), y(Y) {};
    };

    void print_sdl_error_message(std::string);
    void print_debug_message(std::string);
    float hire_time_in_seconds();
};