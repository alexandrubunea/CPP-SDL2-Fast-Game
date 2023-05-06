#include <SDL.h>

#include "../headers/Player.hpp"

Player::Player(): GameObject(0, 0, Utils::Vector2D(0, 0), {0, 0, 0, 0}) {
    score = 0;
}

Player::Player(
    float x,
    float y,
    UINT_32 w,
    UINT_32 h,
    SDL_Rect txt_rect
): GameObject(w, h, Utils::Vector2D(x, y), txt_rect) {
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

void Player::increase_lives() {
    lives++;
}

void Player::decrease_lives() {
    lives--;
}

UINT_32 Player::get_lives() {
    return lives;
}
