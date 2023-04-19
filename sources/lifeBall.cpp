// lifeBall.cpp
#include "lifeBall.h"

lifeBall::lifeBall(/* args */)
{
}

lifeBall::~lifeBall()
{
}

void lifeBall::init(const int& __charmapPosX, const int& __charmapPosY)
{
    charmapPosX = __charmapPosX;
    charmapPosY = __charmapPosY;
    mIsCollected = 0;

    mWidth = LIFE_BALL_WIDTH;
    mHeight = LIFE_BALL_HEIGHT;

}

int lifeBall::getCharmapPosX() const
{
    return charmapPosX;
}

int lifeBall::getCharmapPosY() const
{
    return charmapPosY;
}

void lifeBall::collectLifeBall()
{
    mIsCollected = 1;
}

bool lifeBall::checkIsCollected() const
{
    return mIsCollected;
}

void lifeBall::render(SDL_Renderer* renderer, LTexture& spritesheet)
{
    if (!mIsCollected)
    {
        setSpriteClip(spritesheet, LIFE_BALL_SPRITE_POS_X, LIFE_BALL_SPRITE_POS_Y, 
                        LIFE_BALL_WIDTH / 2, LIFE_BALL_HEIGHT / 2);
        spritesheet.render(renderer, mPosX, mPosY - mHeight, &mSpriteClip, 2);
    }
}