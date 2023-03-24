// mainMenu.cpp

#include "mainMenu.h"

mainMenu::mainMenu()
{

}

mainMenu::~mainMenu()
{

}

mainMenu::mainMenu(SDL_Renderer* __Renderer)
{
    init(__Renderer);
}

void mainMenu::init(SDL_Renderer* __Renderer)
{
    mRenderer = __Renderer;
    
    mBackgroundTexture.loadTexture(mRenderer, &BACKGROUND_PATH[0]);
    mGameLogoTexture.loadTexture(mRenderer, &GAME_LOGO_PATH[0]);
    mSpritesheet.loadTexture(mRenderer, &SPRITESHEET_PATH[0]);

    mNewGameButton.set(mRenderer, NEW_GAME_BUTTON_RENDER_POS_X, NEW_GAME_BUTTON_RENDER_POS_Y, NEW_GAME_BUTTON_TEXT);
    mContinueButton.set(mRenderer, CONTINUE_BUTTON_RENDER_POS_X, CONTINUE_BUTTON_RENDER_POS_Y, CONTINUE_BUTTON_TEXT);
    mInstructionButton.set(mRenderer, INSTRUCTION_BUTTON_RENDER_POS_X, INSTRUCTION_BUTTON_RENDER_POS_Y, INSTRUCTION_BUTTON_TEXT);
    mHighScoreButton.set(mRenderer, HIGH_SCORE_BUTTON_RENDER_POS_X, HIGH_SCORE_BUTTON_RENDER_POS_Y, HIGH_SCORE_BUTTON_TEXT);

    mInstructionMenu.loadInstructionText();
    mHighScoreMenu.set(mRenderer);
}

MAIN_MENU_EXIT_STATUS mainMenu::render()
{
    bool quit = 0;
    SDL_Event curEvent;
    MAIN_MENU_EXIT_STATUS exitStatus = MAIN_MENU_EXIT_NULL;

    bool highScoreOn = 0;
    int instructionPageOn = 0;

    while (!quit)
    {
        while (SDL_PollEvent(&curEvent) != 0)
        {
            if (curEvent.type == SDL_QUIT) quit = 1;

            bool buttonTriggered = 0;

            if (!highScoreOn && !instructionPageOn)
            {
                mNewGameButton.handleEvent(&curEvent, buttonTriggered);
                if (buttonTriggered)
                {
                    quit = 1;
                    exitStatus = MAIN_MENU_EXIT_NEW_GAME;
                }
            }
            
            if (!highScoreOn && !instructionPageOn)
            {
                buttonTriggered = 0;
                mContinueButton.handleEvent(&curEvent, buttonTriggered);
                if (buttonTriggered)
                {
                    quit = 1;
                    exitStatus = MAIN_MENU_EXIT_CONTINUE;
                }
            }

            if (!highScoreOn && !instructionPageOn)
            {
                buttonTriggered = 0;
                mInstructionButton.handleEvent(&curEvent, buttonTriggered);
                if (buttonTriggered)
                {
                    instructionPageOn = 1;
                    mInstructionMenu.set(mRenderer, 1);
                }
            }
            
            if (!highScoreOn && !instructionPageOn)
            {
                buttonTriggered = 0;
                mHighScoreButton.handleEvent(&curEvent, buttonTriggered);
                if (buttonTriggered)
                {
                    highScoreOn = 1;
                }
            }

            if (highScoreOn && !instructionPageOn)
            {
                HIGH_SCORE_MENU_EXIT_STATUS exitStatus = HIGH_SCORE_EXIT_NULL;
                mHighScoreMenu.handleEvent(&curEvent, exitStatus);
                if (exitStatus == HIGH_SCORE_EXIT_RETURN)
                {
                    highScoreOn = 0;
                }
            }

            if (!highScoreOn && instructionPageOn)
            {
                INSTRUCTION_MENU_EXIT_STATUS exitStatus = INSTRUCTION_EXIT_NULL;
                mInstructionMenu.handleEvent(&curEvent, exitStatus);
                if (exitStatus == INSTRUCTION_EXIT_RETURN)
                {
                    instructionPageOn = 0;
                }
                else if (exitStatus == INSTRUCTION_EXIT_NEXT)
                {
                    mInstructionMenu.nextPage(mRenderer);
                }
                else if (exitStatus == INSTRUCTION_EXIT_PREVIOUS)
                {
                    mInstructionMenu.previousPage(mRenderer);
                }
            }
        }

        SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
        SDL_RenderClear(mRenderer);

        mBackgroundTexture.render(mRenderer, 0, 0);
        mGameLogoTexture.render(mRenderer, GAME_LOGO_RENDER_POS_X, GAME_LOGO_RENDER_POS_Y, NULL, GAME_LOGO_RENDER_STRETCH);

        SDL_Rect spriteClip = {SMALL_BALL_SPRITE_POS_x, SMALL_BALL_SPRITE_POS_Y, SMALL_BALL_WIDTH / 2, SMALL_BALL_HEIGHT / 2};
        mSpritesheet.render(mRenderer, DECOR_BALL_RENDER_POS_X, DECOR_BALL_RENDER_POS_Y, &spriteClip, 2);
        
        mNewGameButton.render(mRenderer);
        mContinueButton.render(mRenderer);
        mInstructionButton.render(mRenderer);
        mHighScoreButton.render(mRenderer);

        if (highScoreOn) mHighScoreMenu.render(mRenderer);
        if (instructionPageOn) mInstructionMenu.render(mRenderer);

        SDL_RenderPresent(mRenderer);
    }

    return exitStatus;
}