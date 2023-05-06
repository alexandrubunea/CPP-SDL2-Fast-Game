/*
    Core.hpp
    Contains all the constants and the utility functions
*/

#pragma once

#include <iostream>
#include <fstream>

// Window configuration
#define WIN_WIDTH 540
#define WIN_HEIGHT 650
#define WIN_NAME "Fast!"

// Shortcuts for the integer types
#define INT_16 short int
#define UINT_16 unsigned short int
#define INT_32 int
#define UINT_32 unsigned int
#define INT_64 long long int
#define UINT_64 unsigned long long int

// Player configuration
#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 100
#define PLAYER_Y 500
#define PLAYER_LIVES_CAP 5

// Pickups configuration
#define PICK_UP_WIDTH 10
#define PICK_UP_HEIGHT 10

// Car configuration
#define CAR_DISTANCE 10

// Road configuration
#define WALL_THICKNESS 20
#define BOTTOM_BAR_HEIGHT 50

/*
    NUMBER_OF_LANES macro
    This macro calculates the number of lanes
    based on the window width and the wall thickness
*/
#define NUMBER_OF_LANES(x) \
            (x - WALL_THICKNESS * 2) / PLAYER_WIDTH

// Gameplay configuration
#define BASE_SPEED 1
#define MOVMENT_SPEED 5
#define MAX_CARS_ON_SCREEN 15
#define MAX_PICKUPS_ON_SCREEN 5

#define SLOW_TIME_DURATION 5

#define INITIAL_GAME_SPEED 2

// Key configuration
#define NUMBER_OF_KEYS 4
#define KEY_UP 0
#define KEY_DOWN 1
#define KEY_LEFT 2
#define KEY_RIGHT 3

// SPRITES & TEXTURES
#define CAR_SPRITES_NUMBER 26
#define PLAYER_SPRITES_NUMBER 4
#define PICKUP_SPRITES_NUMBER 4

/*
    Utils namespace
    This namespace contains all the utility functions
*/
namespace Utils {

    /*
        WindowStatus enum
        This enum is used to check the status of the window.
        It can be either running, closed or paused.
    */
    enum WindowStatus {
        WINDOW_RUNNING,
        WINDOW_PAUSED,
        WINDOW_CLOSED
    };

    /*
        PickupType enum
        This enum is used to check the type of the pickup.
        It can be either health, freeze time or clear road.
    */
    enum PickupType {
        SCORE,
        HEALTH,
        SLOW_TIME,
        CLEAR_ROAD
    };

    /*
        Vector2D struct
        This struct is used to represent a 2D vector.
    */
    struct Vector2D {
        float x, y;

        /*
            Vector2D constructor
            This constructor initializes the vector.
            @param X: the x coordinate of the vector
            @param Y: the y coordinate of the vector
        */
        Vector2D(float X=0, float Y=0) :
        x(X), y(Y) {};
    };

    /*
        pair_hash struct
        This struct is used to hash a pair.
    */
    struct pair_hash {
        template <class T1, class T2>
        std::size_t operator() (const std::pair<T1, T2> &pair) const {
            return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
        }
    };

    // Ofstream for the log file
    extern std::ofstream log_file;

    // Debug mode flag
    extern bool DEBUG_MODE; 

    // Crash flag
    extern bool CRASH;

    /*
        set_crash function
        This function sets the crash flag.
        @param crash: the crash flag
    */
    void set_crash(bool);

    /*
        print_sdl_error_message function
        This function prints an SDL error message.
        @param message: the message to print
    */
    void print_sdl_error_message(std::string);

    /*
        print_sdl_image_error_message function
        This function prints an SDL_image error message.
        @param message: the message to print
    */
    void print_sdl_image_error_message(std::string);

    /*
        set_debug_mode function
        This function sets the debug mode flag.
        @param debug_mode: the debug mode flag
    */
    void set_debug_mode(bool);

    /*
        print_debug_message function
        This function prints a debug message.
        @param message: the message to print
    */
    void print_debug_message(std::string);

    /*
        hire_time_in_seconds function
        This function returns the current time in seconds.
    */
    float hire_time_in_seconds();

    /* 
        random_number function
        This function returns a random number between two numbers.
        @param min: the minimum number
        @param max: the maximum number
    */
    INT_32 random_number(INT_32, INT_32);
};