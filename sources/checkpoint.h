// checkpoint.h

/**
 * @brief This file controls the checkpoints on the map
 * Logic:
 * - When a new checkpoint is collected, its appearance change, and old checkpoints
 * are deleted
 * - The starting position is considered a hidden checkpoint and can be deleted
 * - When the ball starts again from a checkpoint, it falls and the screen is scaled again
 * 
 */

#ifndef CHECKPOINT_GUARD
#define CHECKPOINT_GUARD

#include <iostream>
#include <sdl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "base.h"
#include "ball.h"

const int CHECKPOINT_DEFAULT_SPRITE_POS_x = 141;   //position in spritesheet
const int CHECKPOINT_DEFAULT_SPRITE_POS_Y = 1;
const int CHECKPOINT_COLLECTED_SPRITE_POS_x = 183;   //position in spritesheet
const int CHECKPOINT_COLLECTED_SPRITE_POS_Y = 1;
const int CHECKPOINT_WIDTH = 80;
const int CHECKPOINT_HEIGHT = 80;
const double CHECKPOINT_DROP_VELOCITY = 10;
const int CHECKPOINT_SCORE = 20;
enum CHECKPOINT_STATE
{
    CHECKPOINT_HIDDEN,
    CHECKPOINT_DEFAULT,
    CHECKPOINT_COLLECTED,
    CHECKPOINT_DELETED,
};

class checkpoint: public gameObject
{
private:
    CHECKPOINT_STATE mState;

    /// @brief Position of this checkpoint on the charmap
    int charmapPosX, charmapPosY;

    /// @brief Render position if this checkpoint is chosen as the spawn point
    double framePosX, framePosY;   

    /// @brief Check if this checkpoint is active (the ball will spawn here next death)
    bool isActive; 

    /// @brief Check if the ball is large when spawn 
    bool ballSpawnSize;

public:
    checkpoint(/* args */);
    ~checkpoint();

    /// @brief Initialize the checkpoint
    void init(const int& __charmapPosX, const int& __charmapPosY, const CHECKPOINT_STATE& __state = CHECKPOINT_DEFAULT);

    /// @brief Get the position of this checkpoint on the charmap
    int getCharmapPosX() const;
    int getCharmapPosY() const;

    /// @brief Get the default frame scale value of this checkpoint
    double getFramePosX() const;
    double getFramePosY() const;

    void setBallSpawnSize(const bool& isLargeBall);

    bool getBallSpawnSize() const;

    /// @brief Set the position for the ball to start dropping
    void spawnBall(ball& __ball, LTexture& spritesheet);

    /// @brief Change this checkpoint's state
    /// @param newState The new state, chosen from 4 types of flags
    void changeState(const CHECKPOINT_STATE& newState);

    /// @brief Get the current state of the checkpoint
    /// @return A flag represent the corresponding type of state
    CHECKPOINT_STATE getState() const;

    /// @brief Reset the current frame to fit the ball if it is spawned here
    void resetMapFrame(double& __framePosX, double& __framePosY);

    /// @brief Render the checkpoint, depending on the current state
    void render(SDL_Renderer* renderer, LTexture& spritesheet);
};

#endif