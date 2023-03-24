// waterloggedTile.cpp

#include "waterloggedTile.h"

waterloggedTile::waterloggedTile()
{
    setSize(WATERLOGGED_TILE_WIDTH, WATERLOGGED_TILE_HEIGHT);
}

waterloggedTile::waterloggedTile(const int& __PosX, const int& __PosY)
{
    mPosX = __PosX;
    mPosY = __PosY;
    setSize(WATERLOGGED_TILE_WIDTH, WATERLOGGED_TILE_HEIGHT);
}

void waterloggedTile::render(SDL_Renderer* renderer, LTexture& spritesheet)
{
    setSpriteClip(spritesheet, WATERLOGGED_TILE_SPRITE_POS_x, WATERLOGGED_TILE_SPRITE_POS_Y, WATERLOGGED_TILE_WIDTH / 2, WATERLOGGED_TILE_HEIGHT / 2);
    spritesheet.render(renderer, mPosX, mPosY - WATERLOGGED_TILE_HEIGHT, &mSpriteClip, 2);
}