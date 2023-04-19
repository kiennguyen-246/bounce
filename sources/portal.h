// portal.h

/**
 * @brief This file controls the portals of the game
 * Logic:
 * - When the ball collides with a portal, it will be collected (No need to pass through)
 * - When there is no portals left, the exit is open for the ball to pass through.
 * After that, the game moves on to the next level
 * - Some portals are "smaller" than others and cannot let large balls pass through
 */

#ifndef PORTAL_GUARD
#define PORTAL_GUARD

#include "base.h"

const int PORTAL_HORIZONTAL_DEFAULT_SPRITE_POS_x = 767;   //position in spritesheet
const int PORTAL_HORIZONTAL_DEFAULT_SPRITE_POS_Y = 1;
const int PORTAL_HORIZONTAL_COLLECTED_SPRITE_POS_x = 643;   //position in spritesheet
const int PORTAL_HORIZONTAL_COLLECTED_SPRITE_POS_Y = 1;
const int PORTAL_HORIZONTAL_WIDTH = 160;
const int PORTAL_HORIZONTAL_HEIGHT = 80;
const int PORTAL_VERTICAL_DEFAULT_SPRITE_POS_x = 849;   //position in spritesheet
const int PORTAL_VERTICAL_DEFAULT_SPRITE_POS_Y = 1;
const int PORTAL_VERTICAL_COLLECTED_SPRITE_POS_x = 725;   //position in spritesheet
const int PORTAL_VERTICAL_COLLECTED_SPRITE_POS_Y = 1;
const int PORTAL_VERTICAL_WIDTH = 80;
const int PORTAL_VERTICAL_HEIGHT = 160;
const int PORTAL_SCORE = 50;
enum PORTAL_STATE
{
    PORTAL_DEFAULT,
    PORTAL_COLLECTED,
    PORTAL_HORIZONTAL,
    PORTAL_VERTICAL,
    PORTAL_SMALL,
    PORTAL_LARGE
};

class portal: public gameObject
{
private:
    /// @brief Check if the portal is collected
    PORTAL_STATE mIsCollected; 

    /// @brief Check if the portal is vertical
    PORTAL_STATE mOriental;

    /// @brief Check if the portal is larger
    PORTAL_STATE mPortalSize;

    /// @brief Position of this checkpoint on the charmap
    int charmapPosX, charmapPosY;

public:
    portal(/* args */);
    ~portal();

    /// @brief Initialize the portal
    void init(const int& __charmapPosX, const int& __charmapPosY, const PORTAL_STATE& __Oriental, const PORTAL_STATE& __PortalSize);

    /// @brief Get the position of this checkpoint on the charmap
    int getCharmapPosX() const;
    int getCharmapPosY() const;

    void collectPortal();

    PORTAL_STATE getPortalSize() const;

    PORTAL_STATE checkIsCollected() const;

    /// @brief Render the portal, depending on the current state
    void render(SDL_Renderer* renderer, LTexture& spritesheet);
};



#endif