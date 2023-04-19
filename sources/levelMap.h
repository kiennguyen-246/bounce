// levelMap.h

/**
 * @brief This file controls the map of the game and how it is rendered
 * Logic:
 * - Horizontally, the map will move along with the ball. While playing, the ball will "stand still"
 * at some position during the game. The balls position is fixed at 7 brick tiles (560px) from the 
 * leftmost position of the game area.
 * - The map shifts up 7 brick tiles when the ball moves vertically out.
 * - The collide checking function will check colliding objects based on the position of the render map
 */

#ifndef LEVELMAP_GUARD
#define LEVELMAP_GUARD

#include "base.h"
#include "ball.h"
#include "brickTile.h"
#include "levelMap.h"
#include "checkpoint.h"
#include "spike.h"
#include "portal.h"
#include "finishLine.h"
#include "lifeBall.h"
#include "pump.h"
#include "shrinker.h"
#include "trampolineTile.h"
#include "waterloggedTile.h"
#include "accelerator.h"
#include "slopeTile.h"

/**
 * @brief 
 * - B: bricks
 * - R: vertical large portals, together with "+"
 * - r: vertical small portals
 * - E: horizontal small portals, together with "-"
 * - e: horizontal small portals
 * - T: vertical spikes
 * - t: horizontal spikes
 * - C: checkpoints
 * - L: life balls
 * - P: pumps
 * - D: shrinkers
 * - G: Finish line, together with "#"
 * - I: Trampoline tile
 * - 0: Waterlogged tile
 * - S: Accelerator
 */

const char BRICK_CHAR_SYMBOL = 'B';
const char CHECKPOINT_CHAR_SYMBOL = 'C';
const char CHECKPOINT_START_CHAR_SYMBOL = 'c';
const char SPIKE_CHAR_SYMBOL = 'T';
const char SPIKE_HORIZONTAL_CHAR_SYMBOL = 't';
const char PORTAL_VERTICAL_SMALL_CHAR_SYMBOL = 'r';
const char PORTAL_VERTICAL_LARGE_CHAR_SYMBOL = 'R';
const char PORTAL_HORIZONTAL_SMALL_CHAR_SYMBOL = 'e';
const char PORTAL_HORIZONTAL_LARGE_CHAR_SYMBOL = 'E';
const char FINISH_LINE_CHAR_SYMBOL = 'G';
const char LIFE_BALL_CHAR_SYMBOL = 'L';
const char PUMP_CHAR_SYMBOL = 'P';
const char SHRINKER_CHAR_SYMBOL = 'D';
const char TRAMPOLINE_CHAR_SYMBOL = 'I';
const char WATERLOGGED_CHAR_SYMBOL = '0';
const char ACCELERATOR_CHAR_SYMBOL = 'S';
const char SLOPE_CHAR_SYMBOL[] = {',', 'Z', 'X', 'V', 'N'};
const char SLOPE_CHAR_SYMBOL_1 = 'Z';
const char SLOPE_CHAR_SYMBOL_2 = 'X';
const char SLOPE_CHAR_SYMBOL_3 = 'V';
const char SLOPE_CHAR_SYMBOL_4 = 'N';

const int DIRX[] = {1, -1, 0, 0};
const int DIRY[] = {0, 0, 1, -1};


class levelMap
{
private:
    /// @brief The encoded map of the level
    std::vector <std::string> charMap;

    /// @brief List of brick tiles
    std::vector <brickTile> vBrickTiles;

    /// @brief List of slope tiles
    std::vector <slopeTile> vSlopeTiles;

    /// @brief List of trampoline tiles
    std::vector <trampolineTile> vTrampolineTiles;

    /// @brief List of trampoline tiles
    std::vector <waterloggedTile> vWaterloggedTiles;

    /// @brief List of spikes
    std::vector <spike> vSpikes;

    /// @brief List of pumps
    std::vector <pump> vPumps;

    /// @brief List of shrinkers
    std::vector <shrinker> vShrinkers;

    /// @brief List of accelerators
    std::vector <accelerator> vAccelerators;

    /// @brief List of checkpoints
    std::vector <checkpoint> vCheckpoints;

    /// @brief List of life balls
    std::vector <lifeBall> vLifeBalls;

    /// @brief List of portals
    std::vector <portal> vPortals;

    /// @brief The finish line
    finishLine mFinishLine;

    /// @brief The bottom left position of the current frame, in comparison with the full level map
    double curFramePosX, curFramePosY;

    /// @brief Check if a brick tile is free when it is not surrounded by other bricks
    bool isFreeBrickTile(const int& brickTileCharPosX, const int& brickTileCharPosY);

public:
    levelMap(/* args */);
    ~levelMap();

    /// @brief Set up the map by the level
    /// @param id The index of the current level
    void setMap(const int& id, const vector_2d_string& allLevelCharMap);

    std::vector <std::string> getMap();

    /// @brief Move the map horizontally
    /// @param dist Move distance
    void moveX(const double& dist);

    /// @brief Move the map vertically
    /// @param dist Move distance
    void moveY(const double& dist);

    double getFramePosX() const;
    double getFramePosY() const;

    /// @brief Set the bottom left position of the current frame, in comparison with the full level map
    void setFramePos(const double& framePosX, const double& framePosY);

    /// @brief Get the list of brick tiles rendered on the map
    std::vector <brickTile> brickTilesList() const;

    /// @brief Get the list of brick tiles rendered on the map
    std::vector <slopeTile> slopeTilesList() const;

    /// @brief Get the list of trampoline tiles rendered on the map
    std::vector <trampolineTile> trampolineTilesList() const;

    /// @brief Get the list of waterlogged tiles rendered on the map
    std::vector <waterloggedTile> waterloggedTilesList() const;

    /// @brief Get the list of spikes rendered on the map
    std::vector <spike> spikesList() const;

    /// @brief Get the list of pumps rendered on the map
    std::vector <pump> pumpsList() const;

    /// @brief Get the list of shrinkers rendered on the map
    std::vector <shrinker> shrinkersList() const;

    /// @brief Get the list of accelerators rendered on the map
    std::vector <accelerator> acceleratorsList() const;

    /// @brief Get the list of checkpoints in the map
    std::vector <checkpoint> checkpointsList() const;

    /// @brief Get the list of life balls in the map
    std::vector <lifeBall> lifeBallsList() const;

    /// @brief Get the list of portals in the map
    std::vector <portal> portalsList() const;

    finishLine getFinishLine() const;

    /// @brief Update the checkpoints list
    void updateCheckpointsList(const std::vector <checkpoint>& newCheckpointsList);

    /// @brief Update the life balls list
    void updateLifeBallsList(const std::vector <lifeBall>& newLifeBallsList);

    /// @brief Update the portals list
    void updatePortalsList(const std::vector <portal>& newPortalsList);

    /// @brief Update the finish line
    void updateFinishLine(const finishLine& newFinishLine);

    void render(SDL_Renderer* renderer, LTexture& spritesheet);

};

#endif