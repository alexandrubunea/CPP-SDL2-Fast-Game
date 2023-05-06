#include "../headers/Car.hpp"

Car::Car(
    float x,
    float y,
    UINT_32 w,
    UINT_32 h,
    SDL_Rect txt_rect
): GameObject(w, h, Utils::Vector2D(x, y), txt_rect) {
    
}

Car::~Car() {
    
}