#pragma once

#include <iostream>

#define WIN_WIDTH 540
#define WIN_HEIGHT 650
#define WIN_NAME "Fast!"

#define INT_16 short int
#define UINT_16 unsigned short int
#define INT_32 int
#define UINT_32 unsigned int
#define INT_64 long long int
#define UINT_64 unsigned long long int

#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 100
#define PLAYER_Y 500

#define PICK_UP_WIDTH 10
#define PICK_UP_HEIGHT 10

#define CAR_DISTANCE 10

#define WALL_THICKNESS 20

#define BOTTOM_BAR_HEIGHT 50

/* x is the width of the window */
#define NUMBER_OF_LANES(x) \
            (x - WALL_THICKNESS * 2) / PLAYER_WIDTH

#define BASE_SPEED .3
#define MOVMENT_SPEED 5

#define MAX_CARS_ON_SCREEN 15

#define MAX_PICKUPS_ON_SCREEN 5

#define NUMBER_OF_KEYS 4
#define KEY_UP 0
#define KEY_DOWN 1
#define KEY_LEFT 2
#define KEY_RIGHT 3

enum WindowStatus {
    WINDOW_RUNNING,
    WINDOW_PAUSED,
    WINDOW_CLOSED
};

enum PickupType {
    HEALTH,
    FREEZE_TIME,
    CLEAR_ROAD
};

namespace Utils {
    struct Vector2D {
        float x, y;
        Vector2D(float X=0, float Y=0) :
        x(X), y(Y) {};
    };

    struct pair_hash {
        template <class T1, class T2>
        std::size_t operator() (const std::pair<T1, T2> &pair) const {
            return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
        }
    };

    void print_sdl_error_message(std::string);
    void print_debug_message(std::string);
    float hire_time_in_seconds();
    INT_32 random_number(INT_32, INT_32);
};