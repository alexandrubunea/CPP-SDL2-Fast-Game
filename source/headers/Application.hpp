/*
    Application.hpp
    This header file contains the Application class.
*/

#pragma once

#include <iostream>
#include <vector>
#include <bitset>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Core.hpp"
#include "Player.hpp"
#include "Car.hpp"
#include "Pickup.hpp"
#include "GUI/Text.hpp"
#include "GUI/Menu.hpp"


/*
    Application class
    This class is the main class of the game.
    It handles the game loop, the rendering and the gameplay.
*/
class Application {
private:
    UINT_32 WINDOW_WIDTH, WINDOW_HEIGHT; // Window dimensions
    std::string WINDOW_NAME; // Window name

    SDL_Window *window; // SDL window
    SDL_Renderer *renderer; // SDL renderer

    /*
        WindowStatus enum
        This enum is used to check the status of the window.
        It can be either running, closed or paused.
    */
    Utils::WindowStatus WINDOW_STATUS;

    // SDL_Rects for the background, the walls and the bottom bar
    SDL_Rect background_rect;
    SDL_Rect left_wall;
    SDL_Rect right_wall;
    SDL_Rect bottom_bar;

    GUI_Text* score_text; // GUI_Text for the score
    GUI_Text* lives_text; // GUI_Text for the lives

    std::bitset<NUMBER_OF_KEYS> keyboard; // Bitset for the keyboard

    Player player; // Player object

    std::vector<Car> cars; // Vector of cars
    float speed_factor; // Speed factor for the cars

    std::vector<Pickup> pickups; // Vector of pickups

    SDL_Texture *background; // SDL_Texture for the background
    SDL_Texture *cars_spritesheet; // SDL_Texture for the cars spritesheet
    SDL_Texture *pickups_spritesheet; // SDL_Texture for the pickup spritesheet
    
    // Menus
    GUI_Menu* main_menu;
    GUI_Menu* pause_menu;

    /*
        Car sprites
        This array contains the sprites coordinates for the cars.
    */
    const UINT_32 car_sprites[CAR_SPRITES_NUMBER][4] = {
        {7, 16, 52, 135},
        {67, 17, 47, 91},
        {130, 16, 48, 93},
        {190, 16, 48, 97},
        {247, 20, 52, 92},
        {308, 20, 52, 92},
        {367, 20, 52, 92},
        {426, 21, 60, 137},
        {65, 120, 51, 99},
        {127, 120, 51, 99},
        {189, 120, 51, 99},
        {247, 123, 52, 92},
        {308, 123, 52, 92},
        {367, 123, 52, 92},
        {7, 192, 52, 135},
        {64, 226, 55, 103},
        {124, 226, 55, 103},
        {186, 226, 55, 103},
        {248, 226, 55, 103},
        {308, 223, 55, 106},
        {366, 226, 55, 103},
        {10, 346, 45, 86},
        {65, 346, 45, 86},
        {122, 346, 45, 86},
        {178, 346, 45, 86},
        {236, 346, 45, 86}
    };

    /*
        Player sprites
        This array contains the sprites coordinates for the player.
    */
    const UINT_32 player_sprites[PLAYER_SPRITES_NUMBER][4] = {
        {7, 446, 51, 96},
        {72, 446, 51, 96},
        {137, 446, 51, 96},
        {200, 446, 51, 96}
    };

    /*
        Pickup sprites
        This array contains the sprites coordinates for the pickups.
    */
    const UINT_32 pickup_sprites[PICKUP_SPRITES_NUMBER][4] = {
        {0, 0, 10, 10},
        {10, 0, 10, 10},
        {0, 10, 10, 10},
        {10, 10, 10, 10}
    };

private:
    /*
        __loop__ method
        This method is the main loop of the game.
    */
    void __loop__();

    /*
        __controller__ method
        This method handles the input of the game.
    */
    void __controller__(SDL_Event&);

    /*
        __render__ method
        This method handles the rendering of the game.
    */
    void __render__();

    /*
        __gameplay__ method
        This method handles the gameplay of the game.
    */
    void __gameplay__();

    /*
        __spawn_cars__ method
        This method spawns cars.
    */
    void __spawn_cars__();

    /*
        __spawn_pickups__ method
        This method spawns pickups.
    */
    void __spawn_pickups__();

    /*
        __collide_with_cars__ method
        This method checks if the player collides with a car.
        @GameObject&: the object to check the collision with
    */
    bool __collide_with_cars__(GameObject&);

    /*
        __slow_down_cars__ method
        This method slows down the cars.
    */
    void __slow_down_cars__();

    /*
        __load_spritesheets__ method
        This method loads the spritesheets.
    */
    void __load_spritesheets__();

    /*
        __init_player__ method
        This method initializes the player.
    */
    void __init_player__();
public:
    /*
        Application constructor
        This constructor initializes the application.
        @UINT_32: the window width
        @UINT_32: the window height
        @std::string: the window name
    */
    Application(
        UINT_32,
        UINT_32,
        std::string 
    );

    /*
        Application destructor
        This destructor destroys the application.
    */
    ~Application();
};