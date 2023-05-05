/*
    Application.hpp
    This header file contains the Application class.
*/

#pragma once

#include <iostream>
#include <vector>
#include <bitset>
#include <SDL.h>

#include "Core.hpp"
#include "Player.hpp"
#include "Car.hpp"
#include "Pickup.hpp"


/*
    Application class
    This class is the main class of the game.
    It handles the game loop, the rendering and the gameplay.
*/
class Application {
private:
    UINT_32 WINDOW_WIDTH, WINDOW_HEIGHT; // Window dimensions
    std::string WINDOW_NAME; // Window name

    SDL_Window *window; // SDL window
    SDL_Renderer *renderer; // SDL renderer

    /*
        WindowStatus enum
        This enum is used to check the status of the window.
        It can be either running, closed or paused.
    */
    WindowStatus WINDOW_STATUS;

    // SDL_Rects for the background, the walls and the bottom bar
    SDL_Rect background;
    SDL_Rect left_wall;
    SDL_Rect right_wall;
    SDL_Rect bottom_bar;

    std::bitset<NUMBER_OF_KEYS> keyboard; // Bitset for the keyboard

    Player player; // Player object

    std::vector<Car> cars; // Vector of cars
    float speed_factor; // Speed factor for the cars

    std::vector<Pickup> pickups; // Vector of pickups
private:
    /*
        __loop__ method
        This method is the main loop of the game.
    */
    void __loop__();

    /*
        __controller__ method
        This method handles the input of the game.
    */
    void __controller__(SDL_Event&);

    /*
        __render__ method
        This method handles the rendering of the game.
    */
    void __render__();

    /*
        __gameplay__ method
        This method handles the gameplay of the game.
    */
    void __gameplay__();

    /*
        __spawn_cars__ method
        This method spawns cars.
    */
    void __spawn_cars__();

    /*
        __spawn_pickups__ method
        This method spawns pickups.
    */
    void __spawn_pickups__();

    /*
        __collide_with_cars__ method
        This method checks if the player collides with a car.
        @GameObject&: the object to check the collision with
    */
    bool __collide_with_cars__(GameObject&);
public:
    /*
        Application constructor
        This constructor initializes the application.
        @UINT_32: the window width
        @UINT_32: the window height
        @std::string: the window name
    */
    Application(
        UINT_32,
        UINT_32,
        std::string 
    );

    /*
        Application destructor
        This destructor destroys the application.
    */
    ~Application();
};