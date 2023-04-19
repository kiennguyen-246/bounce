// finishLine.h

/**
 * @brief This file controls the finish line of the game
 * Logic:
 * - If the number of collected portals is not enough, the finish line will stay closed
 * - If all portals are collected, the portal will open
 * - After passing through the finish line, the player enters the next level and gains 500 points
 * 
 */

#ifndef FINISHLINE_GUARD
#define FINISHLINE_GUARD

#include "base.h"

const int FINISH_LINE_CLOSED_SPRITE_POS_x = 1;   //position in spritesheet
const int FINISH_LINE_CLOSED_SPRITE_POS_Y = 83;
const int FINISH_LINE_OPEN_SPRITE_POS_x = 881;   //position in spritesheet
const int FINISH_LINE_OPEN_SPRITE_POS_Y = 83;
const int FINISH_LINE_WIDTH = 160;
const int FINISH_LINE_HEIGHT = 160;
const int FINISH_LINE_SCORE = 500;

class finishLine: public gameObject
{
private:
    bool isOpen;
public:
    finishLine();

    finishLine(const int& __PosX, const int& __PosY);

    ~finishLine();

    /// @brief Reset the finish line
    void reset();

    /// @brief Check if the finish line is opened
    bool checkIsOpen() const;

    /// @brief Open the finish line
    void openFinishLine();

    void render(SDL_Renderer* renderer, LTexture& spritesheet);
};


#endif