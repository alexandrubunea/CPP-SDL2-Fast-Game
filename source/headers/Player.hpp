#pragma once

#include <SDL.h>

#include "Core.hpp"
#include "GameObject.hpp"

class Player : public GameObject {
private:

public:
    Player(
        float, 
        float,
        UINT_32, 
        UINT_32
    );
    ~Player();
};