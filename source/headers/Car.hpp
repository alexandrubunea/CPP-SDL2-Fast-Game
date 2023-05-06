/*
    Car.hpp
    This header file contains the Car class.
*/

#pragma once

#include "Core.hpp"
#include "GameObject.hpp"

/*
    Car class
    Represents a car in the game
*/
class Car : public GameObject {
private:

public:
    /*
        Car constructor
        @param x: x position
        @param y: y position
        @param w: width
        @param h: height
    */
    Car(
        float, 
        float,
        UINT_32, 
        UINT_32,
        SDL_Rect
    );

    /*
        Car destructor
    */
    ~Car();
};