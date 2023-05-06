/*
    Pickup.hpp
    This header file contains the Pickup class.
*/

#pragma once

#include "Core.hpp"
#include "GameObject.hpp"

/*
    PickupType enum
    Represents the type of a pickup
*/
class Pickup : public GameObject {
private:
    /*
        PickupType enum
        Represents the type of a pickup
    */
    Utils::PickupType type;

    /*
        INT_32 key
        Represents the key of the pickup
    */
    INT_32 key;
public:

    /*
        Pickup constructor
        @param x: x position
        @param y: y position
        @param w: width
        @param h: height
    */
    Pickup(
        float, 
        float,
        UINT_32, 
        UINT_32,
        Utils::PickupType,
        SDL_Rect
    );

    /*
        Pickup destructor
    */
    ~Pickup();

    /*
        Returns the type of the pickup
    */
    Utils::PickupType get_type();

    /*
        Returns the key of the pickup
    */
    INT_32 get_key();

    /*
        Pickup hash & equal function
    */
    friend struct pickup_hash;
    friend struct pickup_equal;
};

/*
    Pickup hash function
*/
struct pickup_hash {
    std::size_t operator()(const Pickup& p) const {
        return std::hash<INT_32>()(p.key);
    }
};

/*
    Pickup equal function
*/
struct pickup_equal {
    bool operator()(const Pickup& p1, const Pickup& p2) const {
        return p1.key == p2.key;
    }
};