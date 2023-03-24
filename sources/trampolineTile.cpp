// trampolineTile.cpp

#include "trampolineTile.h"

trampolineTile::trampolineTile()
{
    setSize(TRAMPOLINE_TILE_WIDTH, TRAMPOLINE_TILE_HEIGHT);
}

trampolineTile::trampolineTile(const int& __PosX, const int& __PosY)
{
    mPosX = __PosX;
    mPosY = __PosY;
    setSize(TRAMPOLINE_TILE_WIDTH, TRAMPOLINE_TILE_HEIGHT);
}

void trampolineTile::render(SDL_Renderer* renderer, LTexture& spritesheet)
{
    setSpriteClip(spritesheet, TRAMPOLINE_TILE_SPRITE_POS_x, TRAMPOLINE_TILE_SPRITE_POS_Y, TRAMPOLINE_TILE_WIDTH / 2, TRAMPOLINE_TILE_HEIGHT / 2);
    spritesheet.render(renderer, mPosX, mPosY - TRAMPOLINE_TILE_HEIGHT, &mSpriteClip, 2);
}