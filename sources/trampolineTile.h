// trampolineTile.h

/**
 * @brief This file controls the trampoline tiles of the game
 * 
 */

#ifndef TRAMPOLINE_TILE_GUARD
#define TRAMPOLINE_TILE_GUARD

#include <iostream>
#include <sdl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "base.h"

const int TRAMPOLINE_TILE_SPRITE_POS_x = 43;   //position in spritesheet
const int TRAMPOLINE_TILE_SPRITE_POS_Y = 165;
const int TRAMPOLINE_TILE_WIDTH = 80;
const int TRAMPOLINE_TILE_HEIGHT = 80;
const int TRAMPOLINE_SPEED_BOOST_LEVEL = 10;

class trampolineTile: public gameObject
{
private:
    
public:
    /// @brief Default constructor
    trampolineTile();

    /// @brief Create a brick tile that has the bottom left coordinate of (__PosX, __PosY)
    trampolineTile(const int& __PosX, const int& __PosY);

    void render(SDL_Renderer* renderer, LTexture& spritesheet);
};


#endif