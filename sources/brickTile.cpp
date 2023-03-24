// brickTile.cpp

#include "brickTile.h"

brickTile::brickTile()
{
    setSize(BRICK_TILE_WIDTH, BRICK_TILE_HEIGHT);
}

brickTile::brickTile(const int& __PosX, const int& __PosY)
{
    mPosX = __PosX;
    mPosY = __PosY;
    setSize(BRICK_TILE_WIDTH, BRICK_TILE_HEIGHT);
}

void brickTile::render(SDL_Renderer* renderer, LTexture& spritesheet)
{
    setSpriteClip(spritesheet, BRICK_TILE_SPRITE_POS_x, BRICK_TILE_SPRITE_POS_Y, BRICK_TILE_WIDTH / 2, BRICK_TILE_HEIGHT / 2);
    spritesheet.render(renderer, mPosX, mPosY - BRICK_TILE_HEIGHT, &mSpriteClip, 2);
}