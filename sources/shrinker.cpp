// shrinker.cpp

#include "shrinker.h"

shrinker::shrinker()
{
    
}

shrinker::shrinker(const int& x, const int& y)
{
    mPosX = x;
    mPosY = y;
    mWidth = SHRINKER_WIDTH;
    mHeight = SHRINKER_HEIGHT;
    rotateAngle = 0;
}

shrinker::~shrinker()
{
    
}

void shrinker::setRotateAngle(const int& angle)
{
    rotateAngle = angle;
}

void shrinker::render(SDL_Renderer* renderer, LTexture& spritesheet)
{
    setSpriteClip(spritesheet, SHRINKER_SPRITE_POS_x, SHRINKER_SPRITE_POS_Y, SHRINKER_WIDTH / 2, SHRINKER_HEIGHT / 2);

    spritesheet.render(renderer, mPosX, mPosY - mWidth, &mSpriteClip, 2, rotateAngle, NULL);

}