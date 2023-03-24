// accelerator.h

/**
 * @brief This file controls the accelerators of the game
 * 
 */

#ifndef ACCELERATOR_GUARD
#define ACCELERATOR_GUARD

#include <iostream>
#include <sdl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "base.h"

const int ACCELERATOR_SPRITE_POS_x = 517;   //position in spritesheet
const int ACCELERATOR_SPRITE_POS_Y = 1;
const int ACCELERATOR_WIDTH = 80;
const int ACCELERATOR_HEIGHT = 80;
const int ACCELERATOR_ACTIVE_TIME = 300;
const int ACCELERATOR_SPEED_BOOST_LEVEL = 250;

class accelerator: public gameObject
{
private:
    
public:
    /// @brief Default constructor
    accelerator();

    /// @brief Create a brick tile that has the bottom left coordinate of (__PosX, __PosY)
    accelerator(const int& __PosX, const int& __PosY);

    void render(SDL_Renderer* renderer, LTexture& spritesheet);
};


#endif