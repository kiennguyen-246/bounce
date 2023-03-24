// pump.h

/**
 * @brief This file controls the pumps of the game
 * Logic:
 * - When the small ball hit the pump, it will become a large ball.
 * - When the large ball hit the pump, nothing happens
 * 
 */

#ifndef PUMP_GUARD
#define PUMP_GUARD

#include <iostream>
#include <sdl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "base.h"

const int PUMP_SPRITE_POS_x = 559;   //position in spritesheet
const int PUMP_SPRITE_POS_Y = 1;
const int PUMP_WIDTH = 80;
const int PUMP_HEIGHT = 80;

class pump: public gameObject
{
private:
    /// @brief The angle that this spike should be rotated to be attatched to a wall
    int rotateAngle;
public:
    pump();

    /// @brief Construct a spike with a given render position
    pump(const int& x, const int& y);

    ~pump();

    /// @brief Set the angle that this spike should be rotated to be attatched to a wall
    void setRotateAngle(const int& angle);

    /// @brief Render the spike on the screen
    void render(SDL_Renderer* renderer, LTexture& spritesheet);

};

#endif