// lifeBall.h

#ifndef LIFEBALL_GUARD
#define LIFEBALL_GUARD

#include "base.h"

/**
 * @brief This file controls the life balls
 * Logic:
 * - After collecting the life balls, the player gains 1 life and 100 points
 * 
 */

const int LIFE_BALL_SPRITE_POS_X = 391;
const int LIFE_BALL_SPRITE_POS_Y = 1;
const int LIFE_BALL_WIDTH = 80;
const int LIFE_BALL_HEIGHT = 80;
const int LIFE_BALL_SCORE = 100;

class lifeBall: public gameObject
{
private:
    bool mIsCollected;

    /// @brief Position of this checkpoint on the charmap
    int charmapPosX, charmapPosY;
public:
    lifeBall(/* args */);
    ~lifeBall();

    /// @brief Initialize the portal
    void init(const int& __charmapPosX, const int& __charmapPosY);

    /// @brief Get the position of this checkpoint on the charmap
    int getCharmapPosX() const;
    int getCharmapPosY() const;

    void collectLifeBall();

    bool checkIsCollected() const;

    /// @brief Render the portal, depending on the current state
    void render(SDL_Renderer* renderer, LTexture& spritesheet);
};


#endif