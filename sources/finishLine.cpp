// finishLine.cpp

#include "finishLine.h"

finishLine::finishLine()
{
    mWidth = FINISH_LINE_WIDTH;
    mHeight = FINISH_LINE_HEIGHT;
    isOpen = 0;
}

finishLine::finishLine(const int& __PosX, const int& __PosY)
{
    mPosX = __PosX;
    mPosY = __PosY;
    mWidth = FINISH_LINE_WIDTH;
    mHeight = FINISH_LINE_HEIGHT;
    isOpen = 0;
}

finishLine::~finishLine()
{
}

void finishLine::reset()
{
    mPosX = 0;
    mPosY = 0;
    isOpen = 0;
}

bool finishLine::checkIsOpen() const
{
    return isOpen;
}

void finishLine::openFinishLine()
{
    isOpen = 1;
}

void finishLine::render(SDL_Renderer* renderer, LTexture& spritesheet)
{
    if (isOpen) 
    {
        setSpriteClip(spritesheet, FINISH_LINE_OPEN_SPRITE_POS_x, FINISH_LINE_OPEN_SPRITE_POS_Y, mWidth / 2, mHeight / 2);
    }
    else
    {
        setSpriteClip(spritesheet, FINISH_LINE_CLOSED_SPRITE_POS_x, FINISH_LINE_CLOSED_SPRITE_POS_Y, mWidth / 2, mHeight / 2);
    }
    spritesheet.render(renderer, mPosX, mPosY - mWidth, &mSpriteClip, 2);
}