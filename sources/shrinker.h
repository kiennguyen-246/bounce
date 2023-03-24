// shrinker.h

/**
 * @brief This file controls the shrinkers of the game
 * Logic:
 * - When the small ball hit the shrinker, it will become a large ball.
 * - When the large ball hit the shrinker, nothing happens
 * 
 */

#ifndef SHRINKER_GUARD
#define SHRINKER_GUARD

#include <iostream>
#include <sdl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "base.h"

const int SHRINKER_SPRITE_POS_x = 225;   //position in spritesheet
const int SHRINKER_SPRITE_POS_Y = 1;
const int SHRINKER_WIDTH = 80;
const int SHRINKER_HEIGHT = 80;

class shrinker: public gameObject
{
private:
    /// @brief The angle that this spike should be rotated to be attatched to a wall
    int rotateAngle;
public:
    shrinker();

    /// @brief Construct a spike with a given render position
    shrinker(const int& x, const int& y);

    ~shrinker();

    /// @brief Set the angle that this spike should be rotated to be attatched to a wall
    void setRotateAngle(const int& angle);

    /// @brief Render the spike on the screen
    void render(SDL_Renderer* renderer, LTexture& spritesheet);

};

#endif