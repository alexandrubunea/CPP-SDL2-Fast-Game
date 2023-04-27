#include "../headers/Car.hpp"
#include "../headers/Core.hpp"

Car::Car(
    float x,
    float y,
    UINT_32 w,
    UINT_32 h
): GameObject(w, h, Utils::Vector2D(x, y)) {
    
}

Car::~Car() {
    
}