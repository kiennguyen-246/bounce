// waterloggedTile.h

/**
 * @brief This file controls the waterlogged tiles of the game
 * Logic:
 * - When the large ball moves inside waterlogged tiles, it will continuously moves
 * until it reaches the surface with a constant velocity.
 * - When the small ball moves inside waterlogged tiles, it will have its starting velocity
 * decreased by 20%
 * 
 */

#ifndef WATERLOGGEDTILE_GUARD
#define WATERLOGGEDTILE_GUARD

#include "base.h"

const int WATERLOGGED_TILE_SPRITE_POS_x = 295;   //position in spritesheet
const int WATERLOGGED_TILE_SPRITE_POS_Y = 165;
const int WATERLOGGED_TILE_WIDTH = 80;
const int WATERLOGGED_TILE_HEIGHT = 80;
const int WATERLOGGED_TILE_VELOCITY_DECREASE_LEVEL = 20;
const int WATERLOGGED_TILE_ACCELERATION_ADDITION = 1;

class waterloggedTile: public gameObject
{
private:
    
public:
    /// @brief Default constructor
    waterloggedTile();

    /// @brief Create a waterlogged tile that has the bottom left coordinate of (__PosX, __PosY)
    waterloggedTile(const int& __PosX, const int& __PosY);

    void render(SDL_Renderer* renderer, LTexture& spritesheet);
};


#endif