#include <SDL.h>

#include "../headers/Player.hpp"
#include "../headers/Core.hpp"

Player::Player(
    float x,
    float y,
    UINT_32 w,
    UINT_32 h
): GameObject(w, h, Utils::Vector2D(x, y)) {
    
}

Player::~Player() {
    
}