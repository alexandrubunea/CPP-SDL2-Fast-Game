#pragma once

#include <SDL.h>

#include "Core.hpp"

class GameObject {
private:
    UINT_32 WIDTH, HEIGHT;
    Utils::Vector2D position;

    SDL_Rect rect;
    SDL_Color color;
public:
    GameObject(
        UINT_32,
        UINT_32,
        Utils::Vector2D
    );
    ~GameObject();
    void render(SDL_Renderer*);
    void update_position(Utils::Vector2D);

    void change_color(SDL_Color);

    UINT_32 get_width();
    UINT_32 get_height();
    
    bool collide(GameObject&);

    Utils::Vector2D get_position();
};