// slopeTile.h

/**
 * @brief This file controls the slope tiles of the game
 * Logic: 
 * - The ball's acceleration is different while moving along the slope
 * - When falling or jumping and hit a slope tile, the acceleration also change
 * 
 */

#ifndef SLOPETILE_GUARD
#define SLOPETILE_GUARD

#include <iostream>
#include <cmath>
#include <sdl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "base.h"
#include "ball.h"

const int SLOPE_TILE_SPRITE_POS_x[] = {0, 127, 211, 169, 253};   //position in spritesheet
const int SLOPE_TILE_SPRITE_POS_Y[] = {0, 165, 165, 165, 165};
const int SLOPE_TILE_WIDTH = 80;
const int SLOPE_TILE_HEIGHT = 80;

class slopeTile: public gameObject
{
private:
    /// @brief The slope tile are sorted by the order of arcs in the circle (|\ -> /| -> \| -> |/)
    int slopeType;

    /// @brief Equation of the slope line: y = Ax + B
    double mEquationA, mEquationB;

public:
    /// @brief Default constructor
    slopeTile();

    /// @brief Create a brick tile that has the bottom left coordinate of (__PosX, __PosY)
    slopeTile(const int& __PosX, const int& __PosY, const int& __slopeType);

    void setPos(const int& x, const int& y);

    int getSlopeType() const;

    std::pair <double, double> getEquation() const;

    double distanceFromCenter(const ball& __ball) const;

    bool checkBallIsOnSlope(const ball& __ball) const;

    /// @brief Ball is stuck inside the slope tile
    /// @param backToSlope Check if the ball will be going back to the slope or is reflected
    bool checkBallIsInsideSlope(const ball& __ball, bool& backToSlope) const;

    void render(SDL_Renderer* renderer, LTexture& spritesheet);
};


#endif