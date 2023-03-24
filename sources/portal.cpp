// portal.cpp

#include "portal.h"

portal::portal(/* args */)
{
}

portal::~portal()
{
}

void portal::init(const int& __charmapPosX, const int& __charmapPosY, const PORTAL_STATE& __Oriental, const PORTAL_STATE& __PortalSize)
{
    charmapPosX = __charmapPosX;
    charmapPosY = __charmapPosY;
    mOriental = __Oriental;
    mPortalSize = __PortalSize;
    mIsCollected = PORTAL_DEFAULT;

    if (mOriental == PORTAL_HORIZONTAL)
    {
        mWidth = PORTAL_HORIZONTAL_WIDTH;
        mHeight = PORTAL_HORIZONTAL_HEIGHT;
    }
    if (mOriental == PORTAL_VERTICAL)
    {
        mWidth = PORTAL_VERTICAL_WIDTH;
        mHeight = PORTAL_VERTICAL_HEIGHT;
    }

}

int portal::getCharmapPosX() const
{
    return charmapPosX;
}

int portal::getCharmapPosY() const
{
    return charmapPosY;
}

void portal::collectPortal()
{
    mIsCollected = PORTAL_COLLECTED;
}

PORTAL_STATE portal::getPortalSize() const
{
    return mPortalSize;
}

PORTAL_STATE portal::checkIsCollected() const
{
    return mIsCollected;
}

void portal::render(SDL_Renderer* renderer, LTexture& spritesheet)
{
    if (mIsCollected == PORTAL_DEFAULT)
    {
        if (mOriental == PORTAL_VERTICAL)
        {
            setSpriteClip(spritesheet, PORTAL_VERTICAL_DEFAULT_SPRITE_POS_x, PORTAL_VERTICAL_DEFAULT_SPRITE_POS_Y, 
                        PORTAL_VERTICAL_WIDTH / 2, PORTAL_VERTICAL_HEIGHT / 2);
        }
        if (mOriental == PORTAL_HORIZONTAL)
        {
            setSpriteClip(spritesheet, PORTAL_HORIZONTAL_DEFAULT_SPRITE_POS_x, PORTAL_HORIZONTAL_DEFAULT_SPRITE_POS_Y, 
                        PORTAL_HORIZONTAL_WIDTH / 2, PORTAL_HORIZONTAL_HEIGHT / 2);
        }
    }
    if (mIsCollected == PORTAL_COLLECTED)
    {
        if (mOriental == PORTAL_VERTICAL)
        {
            setSpriteClip(spritesheet, PORTAL_VERTICAL_COLLECTED_SPRITE_POS_x, PORTAL_VERTICAL_COLLECTED_SPRITE_POS_Y, 
                        PORTAL_VERTICAL_WIDTH / 2, PORTAL_VERTICAL_HEIGHT / 2);
        }
        if (mOriental == PORTAL_HORIZONTAL)
        {
            setSpriteClip(spritesheet, PORTAL_HORIZONTAL_COLLECTED_SPRITE_POS_x, PORTAL_HORIZONTAL_COLLECTED_SPRITE_POS_Y, 
                        PORTAL_HORIZONTAL_WIDTH / 2, PORTAL_HORIZONTAL_HEIGHT / 2);
        }
    }
    spritesheet.render(renderer, mPosX, mPosY - mHeight, &mSpriteClip, 2);
}