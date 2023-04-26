#pragma once

#include <SDL.h>

#include "Core.hpp"

class GameObject {
private:
    UINT_32 WIDTH, HEIGHT;
    Utils::Vector2D position;

    SDL_Rect rect;
public:
    GameObject(
        UINT_32,
        UINT_32,
        Utils::Vector2D
    );
    ~GameObject();
    void render(SDL_Renderer*);
};