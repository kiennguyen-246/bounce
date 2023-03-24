// spider.cpp
#include "spider.h"

spider::spider(/* args */)
{
}

spider::~spider()
{
}

int spider::getRealPosX() const
{
    return mRealPosX;
}

int spider::getRealPosY() const
{
    return mRealPosY;
}

void spider::init(const spiderInfo& __spiderInfo, LTexture& spritesheet)
{
    mVelocityX = SPIDER_VELOCITY_X;
    mVelocityY = SPIDER_VELOCITY_Y;
    if (__spiderInfo.x1 == __spiderInfo.x2) mVelocityX = 0;
    if (__spiderInfo.y1 == __spiderInfo.y2) mVelocityY = 0;

    mLowerPosX = __spiderInfo.x1 * TILE_WIDTH;
    mLowerPosY = __spiderInfo.y1 * TILE_HEIGHT;
    mUpperPosX = __spiderInfo.x2 * TILE_WIDTH;
    mUpperPosY = __spiderInfo.y2 * TILE_HEIGHT;

    //Vertical move
    if (mVelocityX == 0)
    {
        mRealPosX = TILE_WIDTH * __spiderInfo.x1;
        mRealPosY = TILE_HEIGHT * __spiderInfo.startPos;
    }

    //Horizontal move
    if (mVelocityY == 0)
    {
        mRealPosX = TILE_WIDTH * __spiderInfo.startPos;
        mRealPosY = TILE_HEIGHT * __spiderInfo.y1;
    }

    mWidth = SPIDER_WIDTH;
    mHeight = SPIDER_HEIGHT;

    setSpriteClip(spritesheet, SPIDER_SPRITE_POS_x, SPIDER_SPRITE_POS_Y, SPIDER_WIDTH / 2, SPIDER_HEIGHT / 2);

}

void spider::move()
{
    if (mRealPosX + mVelocityX > mUpperPosX || mRealPosX + mVelocityX < mLowerPosX)
    {
        mVelocityX *= -1;
    }
    mRealPosX += mVelocityX;

    if (mRealPosY + mVelocityY > mUpperPosY || mRealPosY + mVelocityY < mLowerPosY)
    {
        mVelocityY *= -1;
    }
    mRealPosY += mVelocityY;
}

void spider::scaleX(const double& framePos)
{
    mPosX = mRealPosX - framePos;
}

void spider::scaleY(const double& framePos)
{
    mPosY = mRealPosY - framePos;
}

void spider::deleteFromRenderer()
{
    mPosX = 0;
    mPosY = 0;
}

void spider::render(SDL_Renderer* renderer, LTexture& spritesheet)
{
    spritesheet.render(renderer, mPosX, mPosY - mHeight, &mSpriteClip, 2);
}