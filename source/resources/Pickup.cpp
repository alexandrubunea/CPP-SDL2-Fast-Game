#include "../headers/Pickup.hpp"
#include "../headers/Core.hpp"

Pickup::Pickup(
    float x,
    float y,
    UINT_32 w,
    UINT_32 h
): GameObject(w, h, Utils::Vector2D(x, y)) {
    /*
        We generate a random number for the key
        The key is used to identify the pickup
        It will be hashed and compared
    */
    key = Utils::random_number(INT_MIN, INT_MAX);
}

Pickup::~Pickup() {
    
}

PickupType Pickup::get_type() {
    return type;
}

INT_32 Pickup::get_key() {
    return key;
}