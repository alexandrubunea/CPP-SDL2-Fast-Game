#pragma once

#include "Core.hpp"
#include "GameObject.hpp"

class Pickup : public GameObject {
private:
    PickupType type;
    INT_32 key;
public:
    Pickup(
        float, 
        float,
        UINT_32, 
        UINT_32
    );
    ~Pickup();

    PickupType get_type();
    INT_32 get_key();

    friend struct pickup_hash;
    friend struct pickup_equal;
};

struct pickup_hash {
    std::size_t operator()(const Pickup& p) const {
        return std::hash<INT_32>()(p.key);
    }
};

struct pickup_equal {
    bool operator()(const Pickup& p1, const Pickup& p2) const {
        return p1.key == p2.key;
    }
};