// ball.h

/**
 * @brief This file controls the balls types of the game
 * Moving logic:
 * - After the control key is pressed, the ball moves horizontally with an accelerator of -5/64 pixel/(frames)^2
 *   Each time a control key is pressed, the ball starts with a velocity of 5 pixel/frames
 *   The moving equation is X = X0 - 10 * t - (5/8) * (t^2)  (pixel)
 * 
 * - After the control key is pressed, the ball moves vertically with an accelerator of 1/5 pixel/(frames)^2
 *   Each time a control key is pressed, the ball starts with a velocity of 12 pixel/frames
 *   The moving equation is Y = Y0 - 24 * t + (2/5) * (t^2)  (pixel)
 *   For the larger ball, the parameters is a little different. Please check the constants for more information
 * 
 * - Note that the horizontal move and vertical move are independent, so they use different time count
 * 
 * - While moving vertically, if the ball collides with any kind of bricks, it moves in the opposite direction
 *   with the velocity being decreased by 65%. 
 */

#ifndef BALL_GUARD
#define BALL_GUARD

#include <iostream>
#include <sdl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "base.h"

const double SMALL_BALL_VELOCITY_X_DEFAULT = 10.5;     //unit: pixel/frame
const double SMALL_BALL_VELOCITY_Y_DEFAULT = 24;     //unit: pixel/frame
const double SMALL_BALL_ACCELERATION_X_DEFAULT = -5.0 / 8;     //unit: pixel/(frame)^2
const double SMALL_BALL_ACCELERATION_Y_DEFAULT = 4.0 / 5;     //unit: pixel/(frame)^2
const double LARGE_BALL_VELOCITY_X_DEFAULT = 9;     //unit: pixel/frame
const double LARGE_BALL_VELOCITY_Y_DEFAULT = 18;     //unit: pixel/frame
const double LARGE_BALL_VELOCITY_Y_WATERLOGGED = 8;     //unit: pixel/frame
const double LARGE_BALL_ACCELERATION_X_DEFAULT = -5.0 / 8;     //unit: pixel/(frame)^2
const double LARGE_BALL_ACCELERATION_Y_DEFAULT = 63.0 / 200;     //unit: pixel/(frame)^2
const int BALL_BOUNCE_LEVEL = 35;      //new velocity multiplier after a bounce (percent)
const int BALL_MAX_VELOCITY_Y = 50;

const int SMALL_BALL_SPRITE_POS_x = 99;   //position in spritesheet
const int SMALL_BALL_SPRITE_POS_Y = 1;
const int SMALL_BALL_WIDTH = 80;
const int SMALL_BALL_HEIGHT = 80;
const int LARGE_BALL_SPRITE_POS_x = 1;   //position in spritesheet
const int LARGE_BALL_SPRITE_POS_Y = 1;
const int LARGE_BALL_WIDTH = 108;
const int LARGE_BALL_HEIGHT = 108;

const int POPPED_BALL_SPRITE_POS_x = 57;   //position in spritesheet
const int POPPED_BALL_SPRITE_POS_Y = 1;
const int POPPED_BALL_WIDTH = 80;
const int POPPED_BALL_HEIGHT = 80;

class ball: public gameObject
{
private:
    /// @brief The velocity of the ball, by X and Y
    double mVelocityX;
    double mVelocityY;

    /// @brief The real position of the ball (in comparison with the game)
    double mRealPosX;
    double mRealPosY;

    /// @brief The acceleration of the ball
    double mAccelerationX;
    double mAccelerationY;

    /// @brief Number of frames has passed since start moving upward
    int framePassedX;
    int framePassedY;

    /// @brief Check if the ball is enlarged
    bool isLargeBall;

    /// @brief Check if the ball is moving vertically
    bool __isAirborne;

    /// @brief Check if the last collide was the ground(0) or the ceiling(1)
    bool __lastCollideY;

public:
    ball(/* args */);
    ~ball();

    /// @brief Set the position for the ball with some more additional settings
    void setPosEx(const double& x, const double& y, const double& framePosX, const double& framePosY);

    void setAccelerationX(const double& a);

    void setAccelerationY(const double& a);

    double getAccelerationX() const;

    double getAccelerationY() const;

    void setVelocityX(const int& v);

    void setVelocityY(const double& v);

    /// @brief Get the current velocity of the ball
    double getVelocityX() const;

    /// @brief Get the current velocity of the ball
    double getVelocityY() const;

    /// @brief Get the number of frames passed since move starts
    int getFramesPassedX() const;

    /// @brief Get the number of frames passed since move starts
    int getFramesPassedY() const;

    /// @brief Pass 1 frame
    void passFrame();

    /// @brief Reset the number of frames passed since move starts to 0
    void resetFramesPassedX();

    /// @brief Reset the number of frames passed since move starts to 0
    void resetFramesPassedY();

    /// @brief Check if the ball is moving vertically
    bool isAirborne() const;

    /// @brief Set the type of the last collide time, ground(0) or ceiling(1)
    void setCollide(const int& collideType);

    /// @brief Check if the last collide was the ground(0) or the ceiling(1)
    bool lastCollideY() const;

    double getRealPosX() const;
    double getRealPosY() const;

    /// @brief Move the ball horizontally
    /// @return The moved distance
    double moveX();

    /// @brief Undo move horizontally
    void undoMoveX();

    /// @brief Reflect the ball when hitting another block
    void reflectX();

    /// @brief Scale the ball to be rendered in the screen
    void scaleX(const double& framePosX);

    /// @brief Move the ball vertically
    void moveY();

    /// @brief Undo move vertically
    void undoMoveY();

    /// @brief Reflect the ball when hitting another block
    void reflectY();

    /// @brief Scale the ball to be rendered in the screen
    void scaleY(const double& framePos);

    /// @brief Set the ball size to large or small
    void setBallSize(const bool& __isLargeBall, LTexture& spritesheet);

    bool checkIsLargeBall() const;

    double getRadius() const;

    /// @brief Get the center coordinate of the ball
    std::pair <double, double> getBallCenter() const;

    void render(SDL_Renderer* renderer, LTexture& spritesheet);

    /// @brief Render the "pop" animation when hitting enemies
    void renderPopAnimation(SDL_Renderer* renderer, LTexture& spritesheet);
};

#endif