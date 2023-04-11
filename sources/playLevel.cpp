// playLevel.cpp
#include "playLevel.h"

void statusArea::init(SDL_Renderer* renderer, LTexture& spritesheet)
{
    mRenderer = renderer;
    mSpritesheet = spritesheet;
    mContainer = {STATUS_AREA_POS_X, STATUS_AREA_POS_Y, STATUS_AREA_WIDTH, STATUS_AREA_HEIGHT};
    mBallSpriteClip = {SMALL_BALL_SPRITE_POS_x, SMALL_BALL_SPRITE_POS_Y, SMALL_BALL_WIDTH / 2, SMALL_BALL_HEIGHT / 2};
    mPortalSpriteClip = {PORTAL_HORIZONTAL_DEFAULT_SPRITE_POS_x, PORTAL_HORIZONTAL_COLLECTED_SPRITE_POS_Y,
                         PORTAL_HORIZONTAL_WIDTH / 2, PORTAL_HORIZONTAL_HEIGHT / 2};
    mAcceleratorSpriteClip = {ACCELERATOR_SPRITE_POS_x, ACCELERATOR_SPRITE_POS_Y, ACCELERATOR_WIDTH / 2, ACCELERATOR_HEIGHT / 2};
}

void statusArea::renderScore(const int& score)
{
    LTexture curTextTexture;
    std::string scoreStr = std::to_string(score);
    while (scoreStr.size() < 8) scoreStr = "0" + scoreStr;
    renderText(mRenderer, curTextTexture, &scoreStr[0], SCORE_RENDER_POS_X, SCORE_RENDER_POS_Y, 
                STATUS_AREA_FONT_SIZE, &DOSIS_FONT_PATH[0], SDL_COLOR_WHITE);
}

void statusArea::renderPortalsLeft(const int& portalsLeft)
{
    LTexture curTextTexture;
    std::string portalsLeftInfo = std::to_string(portalsLeft) + "x";
    renderText(mRenderer, curTextTexture, &portalsLeftInfo[0], PORTALS_LEFT_TEXT_RENDER_POS_X, PORTALS_LEFT_TEXT_RENDER_POS_Y, 
                STATUS_AREA_FONT_SIZE, &DOSIS_FONT_PATH[0], SDL_COLOR_WHITE);
    mSpritesheet.render(mRenderer, PORTALS_LEFT_SPRITE_RENDER_POS_X, PORTALS_LEFT_SPRITE_RENDER_POS_Y, &mPortalSpriteClip, 2);
}

void statusArea::renderLivesLeft(const int& livesLeft)
{
    LTexture curTextTexture;
    std::string livesInfo = std::to_string(livesLeft) + "x";
    renderText(mRenderer, curTextTexture, &livesInfo[0], LIVES_INFO_TEXT_RENDER_POS_X, LIVES_INFO_TEXT_RENDER_POS_Y, 
                STATUS_AREA_FONT_SIZE, &DOSIS_FONT_PATH[0], SDL_COLOR_WHITE);
    mSpritesheet.render(mRenderer, LIVES_INFO_BALL_SPRITE_RENDER_POS_X, LIVES_INFO_BALL_SPRITE_RENDER_POS_Y, &mBallSpriteClip, 2);
}

void statusArea::renderLevelInfo(const int& levelId)
{
    SDL_SetRenderDrawColor(mRenderer, SDL_COLOR_BLACK.r, SDL_COLOR_BLACK.g, SDL_COLOR_BLACK.b, 255);
    SDL_RenderFillRect(mRenderer, &mContainer);

    LTexture curTextTexture;
    std::string levelInfo = "LEVEL " + std::to_string(levelId);
    renderText(mRenderer, curTextTexture, &levelInfo[0], LEVEL_INFO_TEXT_RENDER_POS_X, LEVEL_INFO_TEXT_RENDER_POS_Y, 
                LEVEL_INFO_TEXT_FONT_SIZE, &DOSIS_FONT_PATH[0], SDL_COLOR_WHITE);
}

void statusArea::renderGameOver()
{
    SDL_SetRenderDrawColor(mRenderer, SDL_COLOR_BLACK.r, SDL_COLOR_BLACK.g, SDL_COLOR_BLACK.b, 255);
    SDL_RenderFillRect(mRenderer, &mContainer);

    LTexture curTextTexture;
    std::string gameOverText = "GAME OVER";
    renderText(mRenderer, curTextTexture, &gameOverText[0], LEVEL_INFO_TEXT_RENDER_POS_X, LEVEL_INFO_TEXT_RENDER_POS_Y, 
                LEVEL_INFO_TEXT_FONT_SIZE, &DOSIS_FONT_PATH[0], SDL_COLOR_WHITE);
}

void statusArea::render(const int& livesLeft, const int& portalsLeft, const int& score, const bool& acceleratorActivated)
{
    SDL_SetRenderDrawColor(mRenderer, SDL_COLOR_BLACK.r, SDL_COLOR_BLACK.g, SDL_COLOR_BLACK.b, 255);
    SDL_RenderFillRect(mRenderer, &mContainer);

    renderLivesLeft(livesLeft);
    renderPortalsLeft(portalsLeft);
    renderScore(score);
    if (acceleratorActivated) mSpritesheet.render(mRenderer, EXTRA_RENDER_POS_X, EXTRA_RENDER_POS_Y, &mAcceleratorSpriteClip, 2);
}

playLevel::playLevel(SDL_Window* __Window, SDL_Renderer* __Renderer, const LTexture& __Spritesheet)
{
    mWindow = __Window;
    mRenderer = __Renderer;
    mSpritesheet = __Spritesheet;
}

playLevel::~playLevel()
{
    
}

void playLevel::setLivesLeft(const int& __livesLeft)
{
    livesLeft = __livesLeft;
}

int playLevel::getLivesLeft() const
{
    return livesLeft;
}

void playLevel::setScore(const int& __score)
{
    score = __score;
}

int playLevel::getScore() const
{
    return score;
}

void playLevel::setLevelId(const int& id, const vector_2d_string& allLevelCharMap, const vector_2d_spiderInfo& allLevelSpidersInfo, const std::vector <int>& allLevelBallSpawnSize)
{
    levelId = id;
    mLevelMap.setMap(id, allLevelCharMap);
    ballSpawnSize = allLevelBallSpawnSize[id];
    initSpiders(allLevelSpidersInfo[id]);
}

void playLevel::initSpiders(const std::vector <spiderInfo>& allLevelSpidersInfo)
{
    mSpiderList.resize(allLevelSpidersInfo.size());
    for (int i = 0; i < int(allLevelSpidersInfo.size()); i ++)
    {
        mSpiderList[i].init(allLevelSpidersInfo[i], mSpritesheet);
    }
}

BLOCK_OBJECT playLevel::getBlockObject() const
{
    auto brickTilesList = mLevelMap.brickTilesList();
    auto trampolineTilesList = mLevelMap.trampolineTilesList();
    auto portalsList = mLevelMap.portalsList();
    auto curFinishLine = mLevelMap.getFinishLine();
    auto pumpsList = mLevelMap.pumpsList();
    auto shrinkersList = mLevelMap.shrinkersList();
    auto acceleratorsList = mLevelMap.acceleratorsList();
    
    BLOCK_OBJECT blockObject = NOT_BLOCKED;

    for (auto &curBrickTile: brickTilesList)
        if (collide(curBrickTile, mBall)) blockObject = BRICK_TILE;

    for (auto &curTrampolineTile: trampolineTilesList)
        if (collide(curTrampolineTile, mBall)) blockObject = TRAMPOLINE_TILE;

    for (auto &curPump: pumpsList)
    {
        if (collide(curPump, mBall))
        {
            blockObject = PUMP_TILE;
        } 
    }

    for (auto &curShrinker: shrinkersList)
    {
        if (collide(curShrinker, mBall))
        {
            blockObject = SHRINKER_TILE;
        } 
    }

    for (auto &curAccelerator: acceleratorsList)
    {
        if (collide(curAccelerator, mBall))
        {
            blockObject = ACCELERATOR_TILE;
        } 
    }
        
    if (collide(curFinishLine, mBall) && !curFinishLine.checkIsOpen()) blockObject = CLOSED_FINISH_LINE_TILES;

    for (auto &curPortal: portalsList)
        if (collide(curPortal, mBall) && mBall.checkIsLargeBall() && curPortal.getPortalSize() == PORTAL_SMALL) blockObject = SMALL_PORTAL_TILES;

    return blockObject;
}

void playLevel::tryMoveX(double& ballPosXBeforeMove, double& ballPosXAfterMove)
{
    if (abs(mBall.getVelocityX()) < 1e-3) return;

    auto slopeTilesList = mLevelMap.slopeTilesList();

    ballPosXBeforeMove = mBall.getRealPosX();
    mBall.moveX();
    mBall.scaleX(mLevelMap.getFramePosX());
    bool backToSlope = 0;
    bool slope = 0;

    for (auto curSlope: mLevelMap.slopeTilesList())
    {
        if (curSlope.checkBallIsInsideSlope(mBall, backToSlope))
        {
            slope = 1;
            if (backToSlope)
            {
                while (curSlope.checkBallIsInsideSlope(mBall, backToSlope))
                {
                    //Move the ball 1 px
                    mBall.setPosEx(mBall.getRealPosX(), mBall.getRealPosY() - (curSlope.getSlopeType() < 3 ? 1 : -1),
                                    mLevelMap.getFramePosX(), mLevelMap.getFramePosY());
                    mBall.scaleY(mLevelMap.getFramePosY());
                }
                mBall.setPosEx(mBall.getRealPosX(), mBall.getRealPosY() + 1, mLevelMap.getFramePosX(), mLevelMap.getFramePosY());
                mBall.scaleY(mLevelMap.getFramePosY());
            }
            else
            {
                mBall.undoMoveX();
                mBall.scaleX(mLevelMap.getFramePosX());
                if (abs(mBall.getVelocityX()) > 1e-3)
                {
                    while (!curSlope.checkBallIsInsideSlope(mBall, backToSlope))
                    {
                        //Move the ball 1 px
                        mBall.setPosEx(mBall.getRealPosX() + mBall.getVelocityX() / abs(mBall.getVelocityX()), mBall.getRealPosY(), mLevelMap.getFramePosX(), mLevelMap.getFramePosY());
                        mBall.scaleX(mLevelMap.getFramePosX());
                    }
                    mBall.setPosEx(mBall.getRealPosX() - mBall.getVelocityX() / abs(mBall.getVelocityX()), mBall.getRealPosY(), mLevelMap.getFramePosX(), mLevelMap.getFramePosY());
                    mBall.scaleX(mLevelMap.getFramePosX());
                } 
                mBall.reflectX();
            }
            // break;
        }
    }

    // if (!slope)
    {
        mCurBlockObjectX = getBlockObject();

        mBall.scaleX(mLevelMap.getFramePosX());

        if (getBlockObject() != NOT_BLOCKED) 
        {
            mBall.undoMoveX();
            mBall.scaleX(mLevelMap.getFramePosX());
            if (abs(mBall.getVelocityX()) > 1e-3)
            {
                while (getBlockObject() == NOT_BLOCKED)
                {
                    //Move the ball 1 px
                    mBall.setPosEx(mBall.getRealPosX() + mBall.getVelocityX() / abs(mBall.getVelocityX()), mBall.getRealPosY(), mLevelMap.getFramePosX(), mLevelMap.getFramePosY());
                    mBall.scaleX(mLevelMap.getFramePosX());
                }
                mCurBlockObjectX = getBlockObject();
                mBall.setPosEx(mBall.getRealPosX() - mBall.getVelocityX() / abs(mBall.getVelocityX()), mBall.getRealPosY(), mLevelMap.getFramePosX(), mLevelMap.getFramePosY());
                mBall.scaleX(mLevelMap.getFramePosX());
            } 
            mBall.reflectX();
        }
    }
    
        

    ballPosXAfterMove = mBall.getRealPosX();

    // std::cout << "[playLevel.cpp] Ball position X after move: " << ballPosXAfterMove << "\n";

    mLevelMap.moveX(ballPosXAfterMove - ballPosXBeforeMove);
    mBall.scaleX(mLevelMap.getFramePosX());
}

void playLevel::tryMoveY()
{
    double ballPosXBeforeMove = mBall.getRealPosX();
    double ballPosYBeforeMove = mBall.getRealPosY();
    mBall.moveY();
    mBall.scaleY(mLevelMap.getFramePosY());

    auto slopeTilesList = mLevelMap.slopeTilesList();
    bool backToSlope = 0;
    bool slope = 0;

    mCurBlockObjectY = getBlockObject();

    for (auto curSlope: slopeTilesList)
    {
        if (curSlope.checkBallIsInsideSlope(mBall, backToSlope))
        {
            slope = 1;
            if (backToSlope)
            {
                while (curSlope.checkBallIsInsideSlope(mBall, backToSlope))
                {
                    mBall.setPosEx(mBall.getRealPosX() + (curSlope.getSlopeType() == 2 || curSlope.getSlopeType() == 3 ? -1 : 1),
                                    mBall.getRealPosY(), mLevelMap.getFramePosX(), mLevelMap.getFramePosY());
                    mBall.scaleX(mLevelMap.getFramePosX());
                }
                mBall.setPosEx(mBall.getRealPosX() - (curSlope.getSlopeType() == 2 || curSlope.getSlopeType() == 3 ? -1 : 1), 
                                mBall.getRealPosY(), mLevelMap.getFramePosX(), mLevelMap.getFramePosY());
                mBall.scaleX(mLevelMap.getFramePosX());
            }
            else
            {
                mBall.undoMoveY();
                mBall.scaleY(mLevelMap.getFramePosY());
                if (mBall.getVelocityY() >= 0)
                {
                    while (!curSlope.checkBallIsInsideSlope(mBall, backToSlope))
                    {
                        mBall.setPosEx(mBall.getRealPosX(), mBall.getRealPosY() + mBall.getRealPosY() / abs(mBall.getRealPosY()), mLevelMap.getFramePosX(), mLevelMap.getFramePosY());
                        mBall.scaleY(mLevelMap.getFramePosY());
                    }
                    mCurBlockObjectY = getBlockObject();
                    mBall.setPosEx(mBall.getRealPosX(), mBall.getRealPosY() - mBall.getRealPosY() / abs(mBall.getRealPosY()), mLevelMap.getFramePosX(), mLevelMap.getFramePosY());
                    mBall.scaleY(mLevelMap.getFramePosY());
                } 
                mBall.reflectY();
            }
            // break;
        }
    }

    // if (!slope)
    {
        if (getBlockObject() != NOT_BLOCKED) 
        {
            mBall.undoMoveY();
            mBall.scaleY(mLevelMap.getFramePosY());
            if (mBall.getVelocityY() >= 0)
            {
                while (getBlockObject() == NOT_BLOCKED)
                {
                    mBall.setPosEx(mBall.getRealPosX(), mBall.getRealPosY() + mBall.getRealPosY() / abs(mBall.getRealPosY()), mLevelMap.getFramePosX(), mLevelMap.getFramePosY());
                    mBall.scaleY(mLevelMap.getFramePosY());
                }
                mCurBlockObjectY = getBlockObject();
                mBall.setPosEx(mBall.getRealPosX(), mBall.getRealPosY() - mBall.getRealPosY() / abs(mBall.getRealPosY()), mLevelMap.getFramePosX(), mLevelMap.getFramePosY());
                mBall.scaleY(mLevelMap.getFramePosY());
            } 
            mBall.reflectY();
        }
    }
    

    double ballPosXAfterMove = mBall.getRealPosX();
    mLevelMap.moveX(ballPosXAfterMove - ballPosXBeforeMove);

    if (mBall.getPosY() < TILE_HEIGHT / 2)
    {
        mBall.undoMoveY();
        mLevelMap.moveY(-7 * TILE_WIDTH);
        mBall.scaleY(mLevelMap.getFramePosY());
        yFrameChanged = 1;
    }
    if (mBall.getPosY() > 8 * TILE_HEIGHT)
    {
        mBall.undoMoveY();
        mLevelMap.moveY(7 * TILE_WIDTH);
        mBall.scaleY(mLevelMap.getFramePosY());
        yFrameChanged = 1;
    }
    //Only move frame vertically when the ball is out of it
}

bool playLevel::checkBallIsAirborne()
{
    int charMapPosX = (mBall.getRealPosX()) / TILE_WIDTH;
    int charMapPosY = (mBall.getRealPosY() + 5) / TILE_HEIGHT;
    switch(mLevelMap.getMap()[charMapPosY][charMapPosX])
    {
        case BRICK_CHAR_SYMBOL:
        case TRAMPOLINE_CHAR_SYMBOL:
        case PUMP_CHAR_SYMBOL:
        case SHRINKER_CHAR_SYMBOL:
        case ACCELERATOR_CHAR_SYMBOL:
            return 0;
        case PORTAL_VERTICAL_SMALL_CHAR_SYMBOL:
        case PORTAL_HORIZONTAL_SMALL_CHAR_SYMBOL:
            if (mBall.checkIsLargeBall()) return 0;
            break;
        default:
            break;
    }

    if (mBall.getRealPosX() + (mBall.checkIsLargeBall() ? LARGE_BALL_WIDTH : SMALL_BALL_WIDTH) - 5 >= (charMapPosX + 1) * TILE_WIDTH)
    {
        switch(mLevelMap.getMap()[charMapPosY][charMapPosX + 1])
        {
            case BRICK_CHAR_SYMBOL:
            case TRAMPOLINE_CHAR_SYMBOL:
            case PUMP_CHAR_SYMBOL:
            case SHRINKER_CHAR_SYMBOL:
            case ACCELERATOR_CHAR_SYMBOL:
                return 0;
            case PORTAL_VERTICAL_SMALL_CHAR_SYMBOL:
            case PORTAL_HORIZONTAL_SMALL_CHAR_SYMBOL:
                if (mBall.checkIsLargeBall()) return 0;
                break;
            default:
                break;
        }
    } 

    if (ballIsOnSlope) return 0;
    
    return 1;
}

bool playLevel::checkBallIsInsideWater()
{
    auto waterloggedTilesList = mLevelMap.waterloggedTilesList();
    auto fakeBall = mBall;
    fakeBall.setPos(mBall.getPosX(), mBall.getPosY() - TILE_HEIGHT / 2);
    
    for (auto &curWaterloggedTile: waterloggedTilesList)
    {
        if (collide(curWaterloggedTile, fakeBall)) return 1;
    }
    return 0;
}

void playLevel::playGame(PLAY_LEVEL_EXIT_STATUS& playLevelStatus)
{
    frameCount = 0;
    
    bool quit = 0;
    SDL_Event curEvent;

    bool levelEnded = 0;
    mGameOverMenu.setVictory(0);
    mGameOverMenu.setScore(0);
    bool gamePaused = 0;
    mPauseButton.set(mRenderer, PAUSE_BUTTON_RENDER_POS_X, PAUSE_BUTTON_RENDER_POS_Y, PAUSE_BUTTON_SPRITE_PATH);
    mPauseMenu.set(mRenderer);

    mStatusArea.init(mRenderer, mSpritesheet);

    bool respawn = 1;
    int lastCheckpointIndex = 0;
    auto checkpointsList = mLevelMap.checkpointsList();
    for (int i = 0; i < checkpointsList.size(); i ++)
    {
        if (checkpointsList[i].getState() == CHECKPOINT_HIDDEN) lastCheckpointIndex = i;
    }    
    checkpointsList[lastCheckpointIndex].setBallSpawnSize(ballSpawnSize);
    
    mLevelMap.updateCheckpointsList(checkpointsList);

    mLevelMap.setFramePos(checkpointsList[lastCheckpointIndex].getFramePosX(), 
                        checkpointsList[lastCheckpointIndex].getFramePosY());

    auto lifeBallsList = mLevelMap.lifeBallsList();
    
    auto portalsList = mLevelMap.portalsList();
    portalsLeft = portalsList.size();

    auto curFinishLine = mLevelMap.getFinishLine();

    int moveXCount = 0;
    
    double lastTrampolineVelocity = -SMALL_BALL_VELOCITY_Y_DEFAULT;

    bool waterlogged = 0;

    int acceleratorStartFrame = 0;
    acceleratorActivated = 0;

    while (!quit)
    {   
        // SDL_Delay(200);
        while (SDL_PollEvent(&curEvent) != 0)
        {
            if (curEvent.type == SDL_QUIT) quit = 1;
            else
            {
                if (levelEnded)
                {
                    GAME_OVER_MENU_EXIT_STATUS gameOverExit = GAME_OVER_EXIT_NULL;
                    mGameOverMenu.handleEvent(&curEvent, gameOverExit);
                    if (gameOverExit == GAME_OVER_EXIT_MAIN_MENU)
                    {
                        playLevelStatus = PLAY_LEVEL_EXIT_MAIN_MENU;
                        quit = 1;
                    }
                    if (gameOverExit == GAME_OVER_EXIT_REPLAY)
                    {
                        playLevelStatus = PLAY_LEVEL_EXIT_REPLAY_LEVEL;
                        quit = 1;
                    }
                }
                if (gamePaused)
                {
                    PAUSE_MENU_EXIT_STATUS pauseExit = PAUSE_EXIT_NULL;
                    mPauseMenu.handleEvent(&curEvent, pauseExit);
                    if (pauseExit == PAUSE_EXIT_MAIN_MENU)
                    {
                        playLevelStatus = PLAY_LEVEL_EXIT_MAIN_MENU;
                        quit = 1;
                    }
                    if (pauseExit == PAUSE_EXIT_RESUME)
                    {
                        // std::cout << "[playLevel.cpp] Run here.\n";
                        gamePaused = 0;
                    }
                }
                else if (!gamePaused)
                {
                    bool buttonTriggered = 0;
                    mPauseButton.handleEvent(&curEvent, buttonTriggered);
                    if (curEvent.type == SDL_KEYDOWN && curEvent.key.keysym.sym == SDLK_ESCAPE) buttonTriggered = 1;
                    if (buttonTriggered) gamePaused = 1;
                }
            }
        }

        frameCount ++;

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

        auto velocityXVal = (mBall.checkIsLargeBall() ? LARGE_BALL_VELOCITY_X_DEFAULT : SMALL_BALL_VELOCITY_X_DEFAULT);
        auto accelerationXVal = (mBall.checkIsLargeBall() ? LARGE_BALL_ACCELERATION_X_DEFAULT : SMALL_BALL_ACCELERATION_X_DEFAULT);
        auto velocityYVal = (mBall.checkIsLargeBall() ? LARGE_BALL_VELOCITY_Y_DEFAULT : SMALL_BALL_VELOCITY_Y_DEFAULT);
        auto accelerationYVal = (mBall.checkIsLargeBall() ? LARGE_BALL_ACCELERATION_Y_DEFAULT : SMALL_BALL_ACCELERATION_Y_DEFAULT);

        if (waterlogged) velocityYVal = velocityYVal * (100 - WATERLOGGED_TILE_VELOCITY_DECREASE_LEVEL) / 100;

        if (acceleratorActivated) velocityXVal = velocityXVal * (ACCELERATOR_SPEED_BOOST_LEVEL) / 100;

        if (!gamePaused && !levelEnded)
        {
            if (currentKeyStates[SDL_SCANCODE_LEFT] || currentKeyStates[SDL_SCANCODE_A]) 
            {
                mBall.resetFramesPassedX();
                mBall.setVelocityX(-velocityXVal);
                mBall.setAccelerationX(-accelerationXVal);
            }

            if (currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_D]) 
            {
                mBall.resetFramesPassedX();
                mBall.setVelocityX(velocityXVal);
                mBall.setAccelerationX(accelerationXVal);
            }

            if (currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_W] || currentKeyStates[SDL_SCANCODE_SPACE])
            {
                if (!checkBallIsAirborne())
                {
                    mBall.resetFramesPassedY();
                    
                    int charMapPosX = mBall.getRealPosX() / TILE_WIDTH;
                    int charMapPosY = (mBall.getRealPosY() + 10) / TILE_HEIGHT;
                    if (mLevelMap.getMap()[charMapPosY][charMapPosX] == TRAMPOLINE_CHAR_SYMBOL || mLevelMap.getMap()[charMapPosY][charMapPosX + 1] == TRAMPOLINE_CHAR_SYMBOL)
                    {
                        if (abs(mBall.getVelocityY()) < 1e-7) mBall.setVelocityY(-velocityYVal * (100 + TRAMPOLINE_SPEED_BOOST_LEVEL) / 100);
                        else mBall.setVelocityY(lastTrampolineVelocity * (100 + TRAMPOLINE_SPEED_BOOST_LEVEL) / 100);
                        if (mBall.getVelocityY() < -BALL_MAX_VELOCITY_Y) mBall.setVelocityY(-BALL_MAX_VELOCITY_Y); 
                        lastTrampolineVelocity = mBall.getVelocityY();
                    }
                    else 
                    {
                        mBall.setVelocityY(-velocityYVal);
                        lastTrampolineVelocity = mBall.getVelocityY();
                    }
                    mBall.setAccelerationY(accelerationYVal);
                }
            }
            else lastTrampolineVelocity = -velocityYVal;
        }

        

        SDL_SetRenderDrawColor(mRenderer, SDL_COLOR_MALIBU.r, SDL_COLOR_MALIBU.g, SDL_COLOR_MALIBU.b, 255);
        SDL_RenderClear(mRenderer);

        //Render the status area
        if (frameCount <= LEVEL_INFO_TEXT_RENDER_TIME) mStatusArea.renderLevelInfo(levelId);
        else mStatusArea.render(livesLeft, portalsLeft, score, acceleratorActivated);

        mLevelMap.render(mRenderer, mSpritesheet);

        if (!gamePaused && !levelEnded)
        {
            for (auto &curSpider: mSpiderList) 
            {
                curSpider.move();
                curSpider.scaleX(mLevelMap.getFramePosX());
                curSpider.scaleY(mLevelMap.getFramePosY());
            }
        }
        

        for (auto &curSpider: mSpiderList)
        {
            if (curSpider.getPosX() < -SPIDER_WIDTH || curSpider.getPosY() > GAMEPLAY_AREA_WIDTH) curSpider.deleteFromRenderer();
            if (curSpider.getPosY() < -SPIDER_HEIGHT || curSpider.getPosY() > GAMEPLAY_AREA_HEIGHT) curSpider.deleteFromRenderer();
            curSpider.render(mRenderer, mSpritesheet);
        } 

        checkpointsList = mLevelMap.checkpointsList();
        lifeBallsList = mLevelMap.lifeBallsList();
        portalsList = mLevelMap.portalsList();
        curFinishLine = mLevelMap.getFinishLine();

        // Hit a trampoline tile
        if (mCurBlockObjectY == TRAMPOLINE_TILE) 
        {
            mBall.setVelocityY(mBall.getVelocityY() * (100 + TRAMPOLINE_SPEED_BOOST_LEVEL) / 100);
        }

        waterlogged = 0;
        if (checkBallIsInsideWater()) waterlogged = 1;

#if CODE787898 == 0
        //Hit a spider
        for (auto &curSpider: mSpiderList)
        {
            if (collide(curSpider, mBall))
            {
                mBall.renderPopAnimation(mRenderer, mSpritesheet);
                mBall.setVelocityX(0);
                mBall.setVelocityY(0);
                livesLeft --;
                respawn = 1;
                break;
            }
        } 
#endif

#if CODE787898 == 0
        //Hit a spike
        for (auto &curSpike: mLevelMap.spikesList())
        {
            if (collide(curSpike, mBall))
            {
                mBall.renderPopAnimation(mRenderer, mSpritesheet);
                mBall.setVelocityX(0);
                mBall.setVelocityY(0);
                livesLeft --;
                respawn = 1;
                break;
            }
            
        }   
#endif

        //Hit a pump
        if (mCurBlockObjectX == PUMP_TILE || mCurBlockObjectY == PUMP_TILE)
        {
            mBall.setBallSize(1, mSpritesheet);
            double ballPosXBeforeMove = mBall.getRealPosX();
            for (auto curPump: mLevelMap.pumpsList())
                if (collide(curPump, mBall))
                {
                    mBall.setPosEx(mBall.getRealPosX() - 20, mBall.getRealPosY(), mLevelMap.getFramePosX(), mLevelMap.getFramePosY());
                }
            double ballPosXAfterMove = mBall.getRealPosX();
            mLevelMap.moveX(ballPosXAfterMove - ballPosXBeforeMove);

            for (auto curPump: mLevelMap.pumpsList())
                if (collide(curPump, mBall))
                {
                    mBall.setPosEx(mBall.getRealPosX(), mBall.getRealPosY() - 20, mLevelMap.getFramePosX(), mLevelMap.getFramePosY());
                }
        }

        //Hit a shrinker
        if (mCurBlockObjectX == SHRINKER_TILE || mCurBlockObjectY == SHRINKER_TILE)
        {
            mBall.setBallSize(0, mSpritesheet);
        }

        //Hit an accelerator
        if (mCurBlockObjectX == ACCELERATOR_TILE || mCurBlockObjectY == ACCELERATOR_TILE)
        {
            acceleratorActivated = 1;
            acceleratorStartFrame = frameCount;
        }
        
        if (frameCount - acceleratorStartFrame > ACCELERATOR_ACTIVE_TIME)
        {
            acceleratorActivated = 0;
            acceleratorStartFrame = 0;
        }

        //Collect a checkpoint
        for (int curIndex = 0; curIndex < checkpointsList.size(); curIndex ++)
        {
            if (collide(checkpointsList[curIndex], mBall))
            {
                switch(checkpointsList[curIndex].getState())
                {
                    case CHECKPOINT_DEFAULT:
                        checkpointsList[lastCheckpointIndex].changeState(CHECKPOINT_DELETED);
                        checkpointsList[curIndex].changeState(CHECKPOINT_COLLECTED);
                        checkpointsList[curIndex].setBallSpawnSize(mBall.checkIsLargeBall());
                        lastCheckpointIndex = curIndex;
                        score += CHECKPOINT_SCORE;
                        break;
                    default:
                        break;
                }
            }
        }
        //Collect a life ball
        for (int curIndex = 0; curIndex < lifeBallsList.size(); curIndex ++)
        {
            if (collide(lifeBallsList[curIndex], mBall))
            {
                if (!lifeBallsList[curIndex].checkIsCollected())
                {
                    lifeBallsList[curIndex].collectLifeBall();
                    score += LIFE_BALL_SCORE;
                    livesLeft ++;
                    if (livesLeft > 5) livesLeft = 5;
                }
            }
        }

        //Collect a portal
        for (int curIndex = 0; curIndex < portalsList.size(); curIndex ++)
        {
            if (collide(portalsList[curIndex], mBall))
            {
                switch(portalsList[curIndex].checkIsCollected())
                {
                    case PORTAL_DEFAULT:
                    {
                        if (portalsList[curIndex].getPortalSize() == PORTAL_LARGE ||
                            (portalsList[curIndex].getPortalSize() == PORTAL_SMALL && mBall.checkIsLargeBall() == 0))
                        {
                            portalsList[curIndex].collectPortal();
                            portalsLeft --;
                            score += PORTAL_SCORE;
                            break;
                        }
                    }
                        
                    default:
                        break;
                }
            }
        }

        if (portalsLeft == 0)
        {
            if (!curFinishLine.checkIsOpen())
            {
                curFinishLine.openFinishLine();
            }
        }

        //Touch the finish line
        if (collide(curFinishLine, mBall))
        {
            if (curFinishLine.checkIsOpen())
            {
                if (!levelEnded) score += FINISH_LINE_SCORE;
                if (levelId < 4)
                {
                    playLevelStatus = PLAY_LEVEL_EXIT_LEVEL_CLEARED;
                    quit = 1;
                }
                else
                {
                    mGameOverMenu.set(mRenderer);
                    mGameOverMenu.setVictory(1);
                    mGameOverMenu.setScore(score);
                    levelEnded = 1;
                }
                
            }
        }
         
        mLevelMap.updateCheckpointsList(checkpointsList);
        mLevelMap.updateLifeBallsList(lifeBallsList);
        mLevelMap.updatePortalsList(portalsList);
        mLevelMap.updateFinishLine(curFinishLine);

        if (respawn)
        {
            if (livesLeft >= MINIMUM_LIFE_COUNT)
            {
                SDL_Delay(200);
                mLevelMap.setFramePos(checkpointsList[lastCheckpointIndex].getFramePosX(), 
                                    checkpointsList[lastCheckpointIndex].getFramePosY());
                checkpointsList[lastCheckpointIndex].spawnBall(mBall, mSpritesheet);
                acceleratorActivated = 0;
                acceleratorStartFrame = 0;
                respawn = 0;
            }
            else
            {
                mGameOverMenu.set(mRenderer);
                mGameOverMenu.setVictory(0);
                mGameOverMenu.setScore(score);
                
                // std::cout << "[playLevel.cpp] Score: " << score << ".\n";
                levelEnded = 1;
            }
        }

        // SDL_Delay(100);

        mBall.passFrame();

        mCurBlockObjectX = NOT_BLOCKED;
        mCurBlockObjectY = NOT_BLOCKED;

        yFrameChanged = 0;

        double ballPosXBeforeMove = 0;
        double ballPosXAfterMove = 0;

        if (waterlogged)
        {
            if (mBall.checkIsLargeBall())
            {
                double v = mBall.getVelocityY();
                v -= WATERLOGGED_TILE_ACCELERATION_ADDITION;
                if (v < -LARGE_BALL_VELOCITY_Y_WATERLOGGED) v = -LARGE_BALL_VELOCITY_Y_WATERLOGGED;
                mBall.setVelocityY(v);
            }
        }

        ballIsOnSlope = 0;
        for (auto curSlope: mLevelMap.slopeTilesList())
        {
            if (curSlope.checkBallIsOnSlope(mBall)) ballIsOnSlope = 1;
        }

        if (ballIsOnSlope)
        {
            // mBall.setAccelerationX(mBall.getAccelerationX() / 2);
            // mBall.setAccelerationY(mBall.getAccelerationY() / 2);
        }
        
        if (!gamePaused && !levelEnded)
        {
            //Try moving by X
            tryMoveX(ballPosXBeforeMove, ballPosXAfterMove);
            
            //Try moving by Y
            tryMoveY();

            if (yFrameChanged && ballPosXBeforeMove != ballPosXAfterMove)
            {
                mBall.undoMoveX();
                mLevelMap.moveX(ballPosXBeforeMove - ballPosXAfterMove);
                mBall.scaleX(mLevelMap.getFramePosX());
            }
        }
        
        mBall.render(mRenderer, mSpritesheet);

        if (gamePaused)
        {
            mPauseMenu.render(mRenderer);
        } 

        if (!levelEnded && !gamePaused) mPauseButton.render(mRenderer);

        if (levelEnded)
        {
            mGameOverMenu.render(mRenderer);
            mStatusArea.renderGameOver();
        }

        SDL_RenderPresent(mRenderer);
    }
}