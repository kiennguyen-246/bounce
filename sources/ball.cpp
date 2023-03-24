// ball.cpp

#include "ball.h"

ball::ball(/* args */)
{

}

ball::~ball()
{
}

void ball::setPosEx(const double& x, const double& y, const double& framePosX, const double& framePosY)
{
    mRealPosX = x;
    mRealPosY = y;
    mPosX = mRealPosX - framePosX;
    mPosY = mRealPosY - framePosY;
}

void ball::setAccelerationX(const double& a)
{
    mAccelerationX = a;
}

void ball::setAccelerationY(const double& a)
{
    mAccelerationY = a;
}

double ball::getAccelerationX() const
{
    return mAccelerationX;
}

double ball::getAccelerationY() const
{
    return mAccelerationY;
}

void ball::setVelocityX(const int& v)
{
    mVelocityX = v;
}

void ball::setVelocityY(const double& v)
{
    mVelocityY = v;
}

double ball::getVelocityX() const
{
    return mVelocityX;
}

double ball::getVelocityY() const
{
    return mVelocityY;
}

int ball::getFramesPassedX() const
{
    return framePassedX;
}

int ball::getFramesPassedY() const
{
    return framePassedY;
}

void ball::passFrame()
{
    framePassedX ++;
    framePassedY ++;
}

void ball::resetFramesPassedX()
{
    framePassedX = 0;
}

void ball::resetFramesPassedY()
{
    framePassedY = 0;
}

bool ball::isAirborne() const
{
    // Δx = v0 * t + a * (t^2) / 2 = (v - a * (t^2) / 2) * t
    double distance = (mVelocityY - mAccelerationY * framePassedY / 2) * framePassedY;
    return (__lastCollideY == 1 || abs(distance) > 1);
}

void ball::setCollide(const int& collideType)
{
    __lastCollideY = collideType;
}

bool ball::lastCollideY() const
{
    return __lastCollideY;
}

double ball::getRealPosX() const
{
    return mRealPosX;
}

double ball::getRealPosY() const
{
    return mRealPosY;
}

double ball::moveX()
{
    //x(t) = x(t - 1) + v(t) - a / 2; v(t) = v(t - 1) + a
    mVelocityX += mAccelerationX;
    mRealPosX += mVelocityX - mAccelerationX / 2;
    return mVelocityX - mAccelerationX / 2;
}

void ball::undoMoveX()
{
    mRealPosX -= mVelocityX - mAccelerationX / 2;
    mVelocityX -= mAccelerationX;
}

void ball::reflectX()
{
    mVelocityX = -mVelocityX * 0;
    mAccelerationX = -mAccelerationX;
    framePassedX = 0;
}

void ball::scaleX(const double& framePos)
{
    mPosX = mRealPosX - framePos;
}

void ball::moveY()
{
    //y(t) = y(t - 1) + v(t) - a / 2; v(t) = v(t - 1) + a
    mVelocityY += mAccelerationY;
    mRealPosY += mVelocityY - mAccelerationY / 2;
}

void ball::undoMoveY()
{
    mRealPosY -= mVelocityY - mAccelerationY / 2;
    mVelocityY -= mAccelerationY;
}

void ball::reflectY()
{
    mVelocityY = -mVelocityY * BALL_BOUNCE_LEVEL / 100;
    framePassedY = 0;
}

void ball::scaleY(const double& framePos)
{
    mPosY = mRealPosY - framePos;
}

void ball::setBallSize(const bool& __isLargeBall, LTexture& spritesheet)
{
    isLargeBall = __isLargeBall;
    if (isLargeBall)
    {
        setSize(LARGE_BALL_WIDTH, LARGE_BALL_HEIGHT);
        setSpriteClip(spritesheet, LARGE_BALL_SPRITE_POS_x, LARGE_BALL_SPRITE_POS_Y, LARGE_BALL_WIDTH / 2, LARGE_BALL_HEIGHT / 2);
    }
    else
    {
        setSize(SMALL_BALL_WIDTH, SMALL_BALL_HEIGHT);
        setSpriteClip(spritesheet, SMALL_BALL_SPRITE_POS_x, SMALL_BALL_SPRITE_POS_Y, SMALL_BALL_WIDTH / 2, SMALL_BALL_HEIGHT / 2);
    }
    
}

bool ball::checkIsLargeBall() const
{
    return isLargeBall;
}

double ball::getRadius() const
{
    return mWidth / 2;
}

std::pair <double, double> ball::getBallCenter() const
{
    return std::make_pair(mPosX + mWidth / 2, mPosY - mHeight / 2);
}

void ball::render(SDL_Renderer* renderer, LTexture& spritesheet)
{
    spritesheet.render(renderer, mPosX, mPosY - mHeight, &mSpriteClip, 2);
}

void ball::renderPopAnimation(SDL_Renderer* renderer, LTexture& spritesheet)
{
    SDL_Rect poppedBallRenderClip = {POPPED_BALL_SPRITE_POS_x, POPPED_BALL_SPRITE_POS_Y, POPPED_BALL_WIDTH / 2, POPPED_BALL_HEIGHT / 2};
    spritesheet.render(renderer, mPosX, mPosY - POPPED_BALL_HEIGHT, &poppedBallRenderClip, 2);
}