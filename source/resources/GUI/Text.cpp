#include "../../headers/GUI/Text.hpp"

GUI_Text::GUI_Text() {
    text = "";
    font_path = "";
    font_size = 0;

    color = { 0, 0, 0, 0 };
    rect = { 0, 0, 0, 0 };
}

GUI_Text::GUI_Text(
    std::string Text,
    std::string FontPath,
    INT_32 FontSize,
    SDL_Color Color,
    SDL_Rect Rect,
    SDL_Renderer *Renderer
) {
    text = Text;
    font_path = FontPath;
    font_size = FontSize;

    color = Color;
    rect = Rect;

    __load_font__();
    __create_texture__(Renderer);
}

GUI_Text::~GUI_Text() {
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

void GUI_Text::__load_font__() {
    font = TTF_OpenFont(font_path.c_str(), font_size);
    if(font == NULL)
        Utils::print_ttf_error_message("Could not load font " + font_path);
    else 
        Utils::print_debug_message("Font loaded successfully");
}

void GUI_Text::__create_texture__(SDL_Renderer *renderer) {
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if(surface == NULL)
        Utils::print_ttf_error_message("Could not create surface for text " + text);
    else {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if(texture == NULL)
            Utils::print_sdl_error_message("Could not create texture for text " + text);
        else 
            Utils::print_debug_message("Texture created successfully");
    }
    SDL_FreeSurface(surface);
}

void GUI_Text::update_text(std::string Text, SDL_Renderer *renderer) {
    text = Text;
    SDL_DestroyTexture(texture);
    __create_texture__(renderer);
}

void GUI_Text::render(SDL_Renderer *renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}