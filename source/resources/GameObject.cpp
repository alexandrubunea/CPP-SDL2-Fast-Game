#include <SDL.h>

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

    color = {255, 255, 255, 255};
}

GameObject::~GameObject() {

};

void GameObject::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(renderer, &rect);
}

void GameObject::update_position(Utils::Vector2D new_position) {
    position = new_position;
    rect.x = (INT_32) position.x;
    rect.y = (INT_32) position.y;
}

UINT_32 GameObject::get_width() {
    return WIDTH;
}
UINT_32 GameObject::get_height() {
    return HEIGHT;
}

void GameObject::change_color(SDL_Color new_color) {
    color = new_color;
}

bool GameObject::collide(GameObject &obj) {
    return (
        (position.x < obj.get_position().x + obj.get_width()) &&
        (position.x + WIDTH > obj.get_position().x) &&
        (position.y < obj.get_position().y + obj.get_height()) &&
        (position.y + HEIGHT > obj.get_position().y)
    );
}

Utils::Vector2D GameObject::get_position() {
    return position;
}