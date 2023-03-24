// spider.h

/**
 * @brief This file controls the spiders types of the game
 * Logic:
 * - The spiders start at a fixed position when the game begins and move in a fixed range
 * - The spiders move even when they are not rendered
 * - If the ball touches a spider, it loses 1 life and respawn at the nearest checkpoint
 */

#ifndef SPIDER_GUARD
#define SPIDER_GUARD

#include <iostream>
#include <sdl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "base.h"

const int SPIDER_SPRITE_POS_x = 309;   //position in spritesheet
const int SPIDER_SPRITE_POS_Y = 1;
const int SPIDER_WIDTH = 160;
const int SPIDER_HEIGHT = 160;
const int SPIDER_VELOCITY_X = 2;    //unit: pixel/frames
const int SPIDER_VELOCITY_Y = 2;

class spider: public gameObject
{
private:
    /// @brief The real position of the spider
    int mRealPosX, mRealPosY;

    /// @brief Spider's moving range
    int mLowerPosX, mLowerPosY;
    int mUpperPosX, mUpperPosY;

    /// @brief The velocity of the spider
    int mVelocityX, mVelocityY;

public:
    spider(/* args */);
    ~spider();

    /// @brief Get the real position of the ball on the map
    int getRealPosX() const;
    int getRealPosY() const;

    /// @brief Initialize the spider based on the given information
    void init(const spiderInfo& __spiderInfo, LTexture& spritesheet);

    /// @brief Move the spider
    void move();

    /// @brief Make the spider to be rendered inside the screen
    void scaleX(const double& framePos);
    void scaleY(const double& framePos);

    /// @brief Delete the spider from the renderer when it strays out of the screen
    void deleteFromRenderer();

    void render(SDL_Renderer* renderer, LTexture& spritesheet);
};

#endif