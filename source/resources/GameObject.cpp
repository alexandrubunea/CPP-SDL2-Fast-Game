#include "../headers/Core.hpp"
#include "../headers/GameObject.hpp"

GameObject::GameObject(
    UINT_32 width,
    UINT_32 height,
    Utils::Vector2D pos
):  WIDTH(width),
    HEIGHT(height),
    position(pos) {
    rect.x = (INT_32) position.x,
    rect.y = (INT_32) position.y,
    rect.w = (INT_32) WIDTH,
    rect.h = (INT_32) HEIGHT;
}

GameObject::~GameObject() {

};

void GameObject::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}