#pragma once

#include <SDL.h>

#include "Text.hpp"
#include "../Core.hpp"

class GUI_Button {
private:
    GUI_Text *text; // GUI_Text
    SDL_Rect button_rect; // SDL_Rect
    SDL_Color button_color; // SDL_Color
    bool selected; // Selected
public:

    /*
        GUI_Button constructor
        This constructor initializes the GUI_Button object.
    */
    GUI_Button();

    /*
        GUI_Button constructor
        This constructor initializes the GUI_Button object.
        @param Text: the text
        @param Position: the position
        @param Width: the width
        @param Height: the height
        @param Padding: the padding
        @param FontSize: the font size
        @param FontPath: the font path
        @param TextColor: the text color
        @param ButtonColor: the button color
        @param Renderer: the renderer
    */
    GUI_Button(
        std::string,
        Utils::Vector2D,
        UINT_32,
        UINT_32,
        UINT_32,
        UINT_32,
        std::string,
        SDL_Color,
        SDL_Color,
        SDL_Renderer*
    );

    /*
        GUI_Button destructor
        This destructor destroys the GUI_Button object.
    */
    ~GUI_Button();

    /*
        render function
        This function renders the GUI_Button object.
        @param Renderer: the renderer
    */
    void render(SDL_Renderer*);

    /*
        select function
        This function switches the selected state.
    */
    void select();
};