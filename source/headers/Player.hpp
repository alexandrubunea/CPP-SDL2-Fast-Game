#pragma once

#include "Core.hpp"
#include "GameObject.hpp"

class Player : public GameObject {
private:
    UINT_32 score;
public:
    Player(
        float, 
        float,
        UINT_32, 
        UINT_32
    );
    ~Player();

    void increase_score(UINT_32);
    UINT_32 get_score();
};