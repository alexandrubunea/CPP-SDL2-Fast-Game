#pragma once

#include <iostream>
#include <SDL.h>

#include "Core.hpp"
#include "Player.hpp"

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
private:
    void __loop__();
    void __controller__(SDL_Event&);
    void __render__();
public:
    Application(
        UINT_32,
        UINT_32,
        std::string 
    );
    ~Application();
};