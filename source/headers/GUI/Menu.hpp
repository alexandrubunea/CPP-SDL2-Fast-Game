#pragma once

#include <vector>
#include "Button.hpp"

class GUI_Menu {
private:
    std::vector<GUI_Button*> buttons; // Buttons
    UINT_32 selected; // Selected
public:
    /*
        GUI_Menu constructor
        This constructor initializes the GUI_Menu object.
    */
    GUI_Menu();

    /*
        GUI_Menu constructor
        This constructor initializes the GUI_Menu object.
        @param Buttons: the buttons
    */
    GUI_Menu(std::vector<GUI_Button*>);

    /*
        GUI_Menu destructor
        This destructor destroys the GUI_Menu object.
    */
    ~GUI_Menu();

    /*
        render function
        This function renders the GUI_Menu object.
        @param Renderer: the renderer
    */
    void render(SDL_Renderer*);

    /*
        select_button function
        This function selects a button.
        @param UINT_32: the index of the button
    */
    void select_button(UINT_32);

    /*
        get_selected_button_id function
        This function returns the id of the selected button.
        @return UINT_32: the id of the selected button
    */
    UINT_32 get_selected_button_id();

};