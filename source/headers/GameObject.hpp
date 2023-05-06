/*
    GameObject.hpp
    This header file contains the GameObject class.
*/

#pragma once

#include <SDL.h>

#include "Core.hpp"

/*
    GameObject class
    Represents a game object
*/
class GameObject {
private:
    UINT_32 WIDTH, HEIGHT; // width and height
    Utils::Vector2D position; // position

    SDL_Rect rect; // rectangle
    SDL_Rect texture_rect; // texture rectangle
    SDL_Color color; // color
public:
    /*
        GameObject constructor
        @param width: width
        @param height: height
        @param pos: position
    */
    GameObject(
        UINT_32,
        UINT_32,
        Utils::Vector2D,
        SDL_Rect
    );

    /*
        GameObject destructor
    */
    ~GameObject();

    /*
        Renders the game object
        @param renderer: renderer
        @param sprite_sheet: sprite sheet

    */
    void render(SDL_Renderer*, SDL_Texture*);

    /*
        Updates the position of the game object
        @param new_position: new position
    */
    void update_position(Utils::Vector2D);

    /*
        Changes the color of the game object
        @param new_color: new color
    */
    void change_color(SDL_Color);

    /*
        Returns the width of the game object
        @return: width
    */
    UINT_32 get_width();

    /*
        Returns the height of the game object
        @return: height
    */
    UINT_32 get_height();
    
    /*
        Checks if the game object collides with another game object
        @param obj: game object
        @return: true if collides, false otherwise
    */
    bool collide(GameObject&);

    /*
        Returns the position of the game object
        @return: position
    */
    Utils::Vector2D get_position();
};