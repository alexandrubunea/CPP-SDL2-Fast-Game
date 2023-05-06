#include "../headers/Pickup.hpp"

Pickup::Pickup(
    float x,
    float y,
    UINT_32 w,
    UINT_32 h,
    Utils::PickupType type,
    SDL_Rect txt_rect
): GameObject(w, h, Utils::Vector2D(x, y), txt_rect) {
    /*
        We generate a random number for the key
        The key is used to identify the pickup
        It will be hashed and compared
    */
    key = Utils::random_number(INT_MIN, INT_MAX);

    this->type = type;
}

Pickup::~Pickup() {
    
}

Utils::PickupType Pickup::get_type() {
    return type;
}

INT_32 Pickup::get_key() {
    return key;
}