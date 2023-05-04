#include <SDL.h>

#include "../headers/Player.hpp"
#include "../headers/Core.hpp"

Player::Player(
    float x,
    float y,
    UINT_32 w,
    UINT_32 h
): GameObject(w, h, Utils::Vector2D(x, y)) {
    score = 0;
}

Player::~Player() {
    
}

void Player::increase_score(UINT_32 amount) {
    score += amount * 10;
}

UINT_32 Player::get_score() {
    return score;
}