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


    /*
        We generate a random chance for the type
        The type is used to identify the pickup
    */
    PickupType types[4] = {
        SCORE,
        HEALTH,
        SLOW_TIME,
        CLEAR_ROAD
    };

    INT_32 chance = Utils::random_number(0, 100);

    if (chance < 80) {
        type = types[0];
        this->change_color({255, 255, 0, 255});
    }
    else if (chance < 90) {
        type = types[1];
        this->change_color({255, 0, 0, 255});
    }
    else if (chance < 95) {
        type = types[2];
        this->change_color({0, 0, 255, 255});
    }
    else {
        type = types[3];
        this->change_color({0, 255, 0, 255});
    }
}

Pickup::~Pickup() {
    
}

PickupType Pickup::get_type() {
    return type;
}

INT_32 Pickup::get_key() {
    return key;
}