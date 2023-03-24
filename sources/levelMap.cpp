// levelMap.cpp
#include "levelMap.h"

levelMap::levelMap(/* args */)
{
}

levelMap::~levelMap()
{
}

bool levelMap::isFreeBrickTile(const int& brickTileCharPosX, const int& brickTileCharPosY)
{
    for (int curDir = 0; curDir < 4; curDir ++)
    {
        int adjBrickX = brickTileCharPosX + DIRX[curDir];
        int adjBrickY = brickTileCharPosY + DIRY[curDir];
        if (adjBrickX < 0 || adjBrickX >= charMap[brickTileCharPosY].size()) continue;
        if (adjBrickY < 0 || adjBrickY >= charMap.size()) continue;
        if (charMap[adjBrickY][adjBrickX] != BRICK_CHAR_SYMBOL) return 1;
    }
    return 0;
}

void levelMap::setMap(const int& id, const vector_2d_string& allLevelCharMap)
{
    charMap = allLevelCharMap[id];

    vBrickTiles.clear();
    vSlopeTiles.clear();
    vTrampolineTiles.clear();
    vWaterloggedTiles.clear();
    vSpikes.clear();
    vCheckpoints.clear();
    vPortals.clear();
    vLifeBalls.clear();
    mFinishLine.reset();

    for (int j = 0; j < charMap.size(); j ++)
        for (int i = 0; i < charMap[j].size(); i ++)
        {
            switch(charMap[j][i])
            {
                case CHECKPOINT_CHAR_SYMBOL:
                {
                    checkpoint curCheckpoint;
                    curCheckpoint.init(i, j);
                    vCheckpoints.push_back(curCheckpoint);
                    break;
                }

                case CHECKPOINT_START_CHAR_SYMBOL:
                {
                    checkpoint curCheckpoint;
                    curCheckpoint.init(i, j, CHECKPOINT_HIDDEN);
                    vCheckpoints.push_back(curCheckpoint);
                    break;
                }

                case PORTAL_VERTICAL_SMALL_CHAR_SYMBOL:
                {
                    portal curPortal;
                    curPortal.init(i, j, PORTAL_VERTICAL, PORTAL_SMALL);
                    vPortals.push_back(curPortal);
                    break;
                }
                    
                case PORTAL_VERTICAL_LARGE_CHAR_SYMBOL:
                {
                    portal curPortal;
                    curPortal.init(i, j, PORTAL_VERTICAL, PORTAL_LARGE);
                    vPortals.push_back(curPortal);
                    break;
                }
                
                case PORTAL_HORIZONTAL_SMALL_CHAR_SYMBOL:
                {
                    portal curPortal;
                    curPortal.init(i, j, PORTAL_HORIZONTAL, PORTAL_SMALL);
                    vPortals.push_back(curPortal);
                    break;
                }
                    
                case PORTAL_HORIZONTAL_LARGE_CHAR_SYMBOL:
                {
                    portal curPortal;
                    curPortal.init(i, j, PORTAL_HORIZONTAL, PORTAL_LARGE);
                    vPortals.push_back(curPortal);
                    break;
                }

                case LIFE_BALL_CHAR_SYMBOL:
                {
                    lifeBall curLifeBall;
                    curLifeBall.init(i, j);
                    vLifeBalls.push_back(curLifeBall);
                    break;
                }

                default: break;

            }

        }
            
}

std::vector <std::string> levelMap::getMap()
{
    return charMap;
}

void levelMap::moveX(const double& dist)
{
    curFramePosX += dist;
}

void levelMap::moveY(const double& dist)
{
    curFramePosY += dist;
}

double levelMap::getFramePosX() const
{
    return curFramePosX;
}

double levelMap::getFramePosY() const
{
    return curFramePosY;
}

void levelMap::setFramePos(const double& framePosX, const double& framePosY)
{
    curFramePosX = framePosX;
    curFramePosY = framePosY;
}

std::vector <brickTile> levelMap::brickTilesList() const
{
    return vBrickTiles;
}

std::vector <slopeTile> levelMap::slopeTilesList() const
{
    return vSlopeTiles;
}

std::vector <trampolineTile> levelMap::trampolineTilesList() const
{
    return vTrampolineTiles;
}

std::vector <waterloggedTile> levelMap::waterloggedTilesList() const
{
    return vWaterloggedTiles;
}

std::vector <spike> levelMap::spikesList() const
{
    return vSpikes;
}

std::vector <pump> levelMap::pumpsList() const
{
    return vPumps;
}

std::vector <shrinker> levelMap::shrinkersList() const
{
    return vShrinkers;
}

std::vector <accelerator> levelMap::acceleratorsList() const
{
    return vAccelerators;
}

std::vector <checkpoint> levelMap::checkpointsList() const
{
    return vCheckpoints;
}

std::vector <lifeBall> levelMap::lifeBallsList() const
{
    return vLifeBalls;
}

std::vector <portal> levelMap::portalsList() const
{
    return vPortals;
}

finishLine levelMap::getFinishLine() const
{
    return mFinishLine;
}

void levelMap::updateCheckpointsList(const std::vector <checkpoint>& newCheckpointsList)
{
    vCheckpoints = newCheckpointsList;
}

void levelMap::updateLifeBallsList(const std::vector <lifeBall>& newLifeBallsList)
{
    vLifeBalls = newLifeBallsList;
}

void levelMap::updatePortalsList(const std::vector <portal>& newPortalsList)
{
    vPortals = newPortalsList;
}   

void levelMap::updateFinishLine(const finishLine& newFinishLine)
{
    mFinishLine = newFinishLine;
}   

void levelMap::render(SDL_Renderer* renderer, LTexture& spritesheet)
{
    int maxCharTileX = GAMEPLAY_AREA_WIDTH / TILE_WIDTH;
    int maxCharTileY = GAMEPLAY_AREA_HEIGHT / TILE_HEIGHT;
    
    int curCharPosX = curFramePosX / TILE_WIDTH;
    int curCharPosY = int(curFramePosY / TILE_HEIGHT / (maxCharTileY - 1)) * (maxCharTileY - 1);
    double remFrameX = curFramePosX - int(curFramePosX / TILE_WIDTH) * TILE_WIDTH;
    // double remFrameY = TILE_HEIGHT - curFramePosY % TILE_HEIGHT;

    vBrickTiles.clear();
    vSlopeTiles.clear();
    vTrampolineTiles.clear();
    vWaterloggedTiles.clear();
    vSpikes.clear();
    vPumps.clear();
    vShrinkers.clear();
    vAccelerators.clear();

    for (auto &i: vPortals) i.setPos(0, 0);
    for (auto &i: vCheckpoints) 
    {
        i.setPos(0, 0);
    }
    for (auto &i: vLifeBalls) i.setPos(0, 0);

    for (int i = 0; i < maxCharTileX + 1; i ++)
    {
        for (int j = 0; j < maxCharTileY; j ++)
        {
            switch(charMap[curCharPosY + j][curCharPosX + i])
            {
                case BRICK_CHAR_SYMBOL:
                {
                    brickTile curBrick(TILE_WIDTH * i - int(remFrameX), TILE_HEIGHT * (j + 1));
                    curBrick.render(renderer, spritesheet);

                    vBrickTiles.push_back(curBrick);

                    break;
                }

                case SLOPE_CHAR_SYMBOL_1:
                case SLOPE_CHAR_SYMBOL_2:
                case SLOPE_CHAR_SYMBOL_3:
                case SLOPE_CHAR_SYMBOL_4:
                {
                    for (int k = 1; k <= 4; k ++)
                        if (charMap[curCharPosY + j][curCharPosX + i] == SLOPE_CHAR_SYMBOL[k])
                        {
                            slopeTile curSlope(TILE_WIDTH * i - int(remFrameX), TILE_HEIGHT * (j + 1), k);
                            curSlope.render(renderer, spritesheet);
                            vSlopeTiles.push_back(curSlope);
                        }
                    break;
                }

                case TRAMPOLINE_CHAR_SYMBOL:
                {
                    trampolineTile curTrampoline(TILE_WIDTH * i - int(remFrameX), TILE_HEIGHT * (j + 1));
                    curTrampoline.render(renderer, spritesheet);

                    vTrampolineTiles.push_back(curTrampoline);

                    break;
                }

                case WATERLOGGED_CHAR_SYMBOL:
                {
                    waterloggedTile curWaterlogged(TILE_WIDTH * i - int(remFrameX), TILE_HEIGHT * (j + 1));
                    curWaterlogged.render(renderer, spritesheet);

                    vWaterloggedTiles.push_back(curWaterlogged);

                    break;
                }

                case SPIKE_HORIZONTAL_CHAR_SYMBOL:
                {
                    spike curSpike(SPIKE_WIDTH * i - int(remFrameX), SPIKE_HEIGHT * (j + 1));

                    if (charMap[curCharPosY + j][curCharPosX + i + 1] == BRICK_CHAR_SYMBOL) 
                        curSpike.setRotateAngle(270);
                    else if (charMap[curCharPosY + j][curCharPosX + i - 1] == BRICK_CHAR_SYMBOL) 
                        curSpike.setRotateAngle(90);

                    curSpike.render(renderer, spritesheet);

                    vSpikes.push_back(curSpike);

                    break;
                }

                case SPIKE_CHAR_SYMBOL:
                {
                    spike curSpike(SPIKE_WIDTH * i - int(remFrameX), SPIKE_HEIGHT * (j + 1));

                    if (charMap[curCharPosY + j + 1][curCharPosX + i] == BRICK_CHAR_SYMBOL) 
                        curSpike.setRotateAngle(0);
                    else if (charMap[curCharPosY + j - 1][curCharPosX + i] == BRICK_CHAR_SYMBOL) 
                        curSpike.setRotateAngle(180);

                    curSpike.render(renderer, spritesheet);

                    vSpikes.push_back(curSpike);

                    break;
                }
                    
                case CHECKPOINT_CHAR_SYMBOL:
                case CHECKPOINT_START_CHAR_SYMBOL:
                {
                    for (auto &curCheckpoint: vCheckpoints)
                    {
                        if (curCheckpoint.getCharmapPosX() != curCharPosX + i || curCheckpoint.getCharmapPosY() != curCharPosY + j)
                        {
                            continue;
                        } 
                        else
                        {
                            curCheckpoint.setPos(TILE_WIDTH * i - int(remFrameX), TILE_HEIGHT * (j + 1));
                            curCheckpoint.render(renderer, spritesheet);
                        }
                        
                    }
                    break;
                }

                case PORTAL_VERTICAL_SMALL_CHAR_SYMBOL:
                case PORTAL_VERTICAL_LARGE_CHAR_SYMBOL:
                {
                    for (auto &curPortal: vPortals)
                    {
                        if (curPortal.getCharmapPosX() != curCharPosX + i || curPortal.getCharmapPosY() != curCharPosY + j)
                        {
                            continue;
                        }
                        else
                        {
                            curPortal.setPos(TILE_WIDTH * i - int(remFrameX), TILE_HEIGHT * (j + 1));
                            curPortal.render(renderer, spritesheet);
                        }
                        
                    }
                    break;
                }

                case PORTAL_HORIZONTAL_SMALL_CHAR_SYMBOL:
                case PORTAL_HORIZONTAL_LARGE_CHAR_SYMBOL:
                {
                    for (auto &curPortal: vPortals)
                    {
                        if (curPortal.getCharmapPosX() != curCharPosX + i || curPortal.getCharmapPosY() != curCharPosY + j)
                        {
                            continue;
                        }
                        else
                        {
                            curPortal.setPos(TILE_WIDTH * i - int(remFrameX), TILE_HEIGHT * (j + 1));
                            curPortal.render(renderer, spritesheet);
                        }
                        
                    }
                    break;
                }

                case FINISH_LINE_CHAR_SYMBOL:
                {
                    mFinishLine.setPos(TILE_WIDTH * i - int(remFrameX), TILE_HEIGHT * (j + 1));
                    mFinishLine.render(renderer, spritesheet);
                    break;
                }

                case LIFE_BALL_CHAR_SYMBOL:
                {
                    for (auto &curLifeBall: vLifeBalls)
                    {
                        if (curLifeBall.getCharmapPosX() != curCharPosX + i || curLifeBall.getCharmapPosY() != curCharPosY + j) 
                        {
                            continue;
                        }
                        else
                        {
                            curLifeBall.setPos(TILE_WIDTH * i - int(remFrameX), TILE_HEIGHT * (j + 1));
                            curLifeBall.render(renderer, spritesheet);
                        }
                        
                    }
                    break;
                }

                case PUMP_CHAR_SYMBOL:
                {
                    pump curPump(PUMP_WIDTH * i - int(remFrameX), PUMP_HEIGHT * (j + 1));

                    if (charMap[curCharPosY + j + 1][curCharPosX + i] == BRICK_CHAR_SYMBOL) 
                        curPump.setRotateAngle(0);
                    else if (charMap[curCharPosY + j - 1][curCharPosX + i] == BRICK_CHAR_SYMBOL) 
                        curPump.setRotateAngle(180);

                    curPump.render(renderer, spritesheet);

                    vPumps.push_back(curPump);

                    break;
                }

                case SHRINKER_CHAR_SYMBOL:
                {
                    shrinker curShrinker(SHRINKER_WIDTH * i - int(remFrameX), SHRINKER_HEIGHT * (j + 1));

                    if (charMap[curCharPosY + j - 1][curCharPosX + i] == BRICK_CHAR_SYMBOL) 
                        curShrinker.setRotateAngle(180);

                    curShrinker.render(renderer, spritesheet);

                    vShrinkers.push_back(curShrinker);

                    break;
                }

                case ACCELERATOR_CHAR_SYMBOL:
                {
                    accelerator curAccelerator(ACCELERATOR_WIDTH * i - int(remFrameX), ACCELERATOR_HEIGHT * (j + 1));

                    curAccelerator.render(renderer, spritesheet);

                    vAccelerators.push_back(curAccelerator);

                    break;
                }

                default: break;

            }
            

        }
    }

}