// pump.cpp

#include "pump.h"

pump::pump()
{
    
}

pump::pump(const int& x, const int& y)
{
    mPosX = x;
    mPosY = y;
    mWidth = PUMP_WIDTH;
    mHeight = PUMP_HEIGHT;
}

pump::~pump()
{
    
}

void pump::setRotateAngle(const int& angle)
{
    rotateAngle = angle;
}

void pump::render(SDL_Renderer* renderer, LTexture& spritesheet)
{
    setSpriteClip(spritesheet, PUMP_SPRITE_POS_x, PUMP_SPRITE_POS_Y, PUMP_WIDTH / 2, PUMP_HEIGHT / 2);

    spritesheet.render(renderer, mPosX, mPosY - mWidth, &mSpriteClip, 2, rotateAngle, NULL);

}