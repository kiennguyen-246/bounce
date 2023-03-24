// accelerator.cpp

#include "accelerator.h"

accelerator::accelerator()
{
    setSize(ACCELERATOR_WIDTH, ACCELERATOR_HEIGHT);
}

accelerator::accelerator(const int& __PosX, const int& __PosY)
{
    mPosX = __PosX;
    mPosY = __PosY;
    setSize(ACCELERATOR_WIDTH, ACCELERATOR_HEIGHT);
}

void accelerator::render(SDL_Renderer* renderer, LTexture& spritesheet)
{
    setSpriteClip(spritesheet, ACCELERATOR_SPRITE_POS_x, ACCELERATOR_SPRITE_POS_Y, ACCELERATOR_WIDTH / 2, ACCELERATOR_HEIGHT / 2);
    spritesheet.render(renderer, mPosX, mPosY - ACCELERATOR_HEIGHT, &mSpriteClip, 2);
}