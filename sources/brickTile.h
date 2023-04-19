// brickTile.h

/**
 * @brief This file controls the brick tiles of the game
 * 
 */

#ifndef BRICKTILE_GUARD
#define BRICKTILE_GUARD

#include "base.h"

const int BRICK_TILE_SPRITE_POS_x = 85;   //position in spritesheet
const int BRICK_TILE_SPRITE_POS_Y = 165;
const int BRICK_TILE_WIDTH = 80;
const int BRICK_TILE_HEIGHT = 80;

class brickTile: public gameObject
{
private:
    
public:
    /// @brief Default constructor
    brickTile();

    /// @brief Create a brick tile that has the bottom left coordinate of (__PosX, __PosY)
    brickTile(const int& __PosX, const int& __PosY);

    void render(SDL_Renderer* renderer, LTexture& spritesheet);
};


#endif