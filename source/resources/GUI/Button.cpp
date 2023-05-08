#include "../../headers/GUI/Button.hpp"

GUI_Button::GUI_Button() {
    text = NULL;
    button_rect = { 0, 0, 0, 0 };
    button_color = { 0, 0, 0, 0 };
    selected = false;
}

GUI_Button::GUI_Button(
    std::string Text,
    Utils::Vector2D Position,
    UINT_32 Width,
    UINT_32 Height,
    UINT_32 Padding,
    UINT_32 FontSize,
    std::string FontPath,
    SDL_Color TextColor,
    SDL_Color ButtonColor,
    SDL_Renderer *Renderer
) {
    text = new GUI_Text(
        Text,
        FontPath,
        FontSize,
        TextColor,
        { 
            (INT_32) (Position.x + Padding),
            (INT_32) (Position.y + Padding),
            (INT_32) (Width - Padding),
            (INT_32) (Height - Padding)
         },
        Renderer
    );

    button_rect = {
        (INT_32) Position.x,
        (INT_32) Position.y,
        (INT_32) Width,
        (INT_32) Height
    };

    button_color = ButtonColor;
    selected = false;
}

GUI_Button::~GUI_Button() {
    delete text;
}

void GUI_Button::render(SDL_Renderer *renderer) {
    if(selected) {
        SDL_Rect border = {
            button_rect.x - 2,
            button_rect.y - 2,
            button_rect.w + 4,
            button_rect.h + 4
        };

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &border);
    }

    SDL_SetRenderDrawColor(renderer, button_color.r, button_color.g, button_color.b, button_color.a);
    SDL_RenderFillRect(renderer, &button_rect);

    text->render(renderer);
}

void GUI_Button::select() {
    selected = !selected;
}