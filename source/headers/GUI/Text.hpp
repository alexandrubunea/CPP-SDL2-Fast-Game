#pragma once

#include <SDL_ttf.h>

#include "../Core.hpp"

class GUI_Text {
private:
    std::string text; // Text
    std::string font_path; // Font path
    INT_32 font_size; // Font size

    TTF_Font *font; // TTF_Font

    SDL_Color color; // Color
    SDL_Rect rect; // SDL_Rect

    SDL_Texture *texture; // SDL_Texture

private:
    /*
        load_font function
        This function loads the font.
    */
    void __load_font__();

    /*
        load_texture function
        This function loads the texture.
    */
    void __create_texture__(SDL_Renderer*);

public:
    /*
        GUI_Text constructor
        This constructor initializes the GUI_Text object.
    */
    GUI_Text();
    
    /*
        GUI_Text constructor
        This constructor initializes the GUI_Text object.
        @param Text: the text
        @param FontPath: the font path
        @param FontSize: the font size
        @param Color: the color
        @param Rect: the SDL_Rect
    */
    GUI_Text(
        std::string,
        std::string,
        INT_32,
        SDL_Color,
        SDL_Rect,
        SDL_Renderer*
    );

    /*
        GUI_Text destructor
        This destructor destroys the GUI_Text object.
    */
    ~GUI_Text();

    /*
        set_text function
        This function sets the text.
        @param Text: the text
    */
    void render(SDL_Renderer*);

    void update_text(std::string, SDL_Renderer*);
};