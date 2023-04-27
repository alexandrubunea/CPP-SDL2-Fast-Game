#pragma once

#include "Core.hpp"
#include "GameObject.hpp"

class Player : public GameObject {
private:
    float booster = 1.0;
public:
    Player(
        float, 
        float,
        UINT_32, 
        UINT_32
    );
    ~Player();
};