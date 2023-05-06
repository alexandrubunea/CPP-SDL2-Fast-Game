/*
    Player.hpp
    This header file contains the Player class.
*/

#pragma once

#include "Core.hpp"
#include "GameObject.hpp"

/*
    Player class
    Represents the player in the game
*/
class Player : public GameObject {
private:
    UINT_32 score; // score
    UINT_32 lives; // lives
public:
    /*
        Default Player constructor
    */
    Player();

    /*
        Player constructor
        @param x: x position
        @param y: y position
        @param w: width
        @param h: height
    */
    Player(
        float, 
        float,
        UINT_32, 
        UINT_32,
        SDL_Rect
    );
    
    /*
        Player destructor
    */
    ~Player();

    /*
        Increases the score of the player
        @param amount: amount to increase the score by
    */
    void increase_score(UINT_32);

    /*
        Returns the score of the player
    */
    UINT_32 get_score();

    /*
        Increases the lives of the player
    */
    void increase_lives();

    /*
        Decreases the lives of the player
    */
    void decrease_lives();

    /*
        Returns the lives of the player
    */
    UINT_32 get_lives();
};