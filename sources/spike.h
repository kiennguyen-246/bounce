// enemy.h

/**
 * @brief This file controls the enemies, including spikes and spiders
 * Spike logic:
 * - The spikes are only rendered on the map and is not saved while playing
 * - The spikes are always attatched to at least 1 brick tile
 * - When hitting spike, the ball will explode and respawn again at the 
 * nearest checkpoint. 1 life is taken away.
 */

#ifndef ENEMY_GUARD
#define ENEMY_GUARD

#include <iostream>
#include <sdl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "base.h"

const int SPIKE_SPRITE_POS_x = 891;   //position in spritesheet
const int SPIKE_SPRITE_POS_Y = 1;
const int SPIKE_WIDTH = 80;
const int SPIKE_HEIGHT = 80;

class spike: public gameObject
{
private:
    /// @brief The angle that this spike should be rotated to be attatched to a wall
    int rotateAngle;
public:
    spike();

    /// @brief Construct a spike with a given render position
    spike(const int& x, const int& y);

    ~spike();

    /// @brief Set the angle that this spike should be rotated to be attatched to a wall
    void setRotateAngle(const int& angle);

    /// @brief Render the spike on the screen
    void render(SDL_Renderer* renderer, LTexture& spritesheet);

};

#endif