#include "../../headers/GUI/Menu.hpp"

GUI_Menu::GUI_Menu() {
    selected = 0;
}

GUI_Menu::GUI_Menu(std::vector<GUI_Button*> Buttons) {
    buttons = Buttons;
    selected = 0;
}

GUI_Menu::~GUI_Menu() {
    for(UINT_32 i = 0; i < buttons.size(); i++) {
        delete buttons[i];
    }
}

void GUI_Menu::render(SDL_Renderer *renderer) {
    for(UINT_32 i = 0; i < buttons.size(); i++) {
        buttons[i]->render(renderer);
    }
}

void GUI_Menu::select_button(UINT_32 id) {
    selected = id;
}

UINT_32 GUI_Menu::get_selected_button_id() {
    return selected;
}
