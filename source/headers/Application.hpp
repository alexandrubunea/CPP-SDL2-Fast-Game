#pragma once

#include <iostream>
#include <vector>
#include <SDL.h>

#include "Core.hpp"
#include "Player.hpp"
#include "Car.hpp"

class Application {
private:
    UINT_32 WINDOW_WIDTH, WINDOW_HEIGHT;
    std::string WINDOW_NAME;

    SDL_Window *window;
    SDL_Renderer *renderer;

    WindowStatus WINDOW_STATUS;

    SDL_Rect background;
    SDL_Rect left_wall;
    SDL_Rect right_wall;
    SDL_Rect bottom_bar;

    Player player;

    std::vector<Car> cars;
private:
    void __loop__();
    void __controller__(SDL_Event&);
    void __render__();
    void __gameplay__();
    void __spawn_cars__();
public:
    Application(
        UINT_32,
        UINT_32,
        std::string 
    );
    ~Application();
};