// mainMenu.h
/**
 * @brief This file controls a main menu level of the game
 * 
 */

#ifndef MAINMENU_GUARD
#define MAINMENU_GUARD

#include <iostream>
#include <string>
#include <windows.h>
#include <sdl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "base.h"
#include "buttons.h"
#include "miniMenu.h"
#include "ball.h"

enum MAIN_MENU_EXIT_STATUS
{
    MAIN_MENU_EXIT_NULL,
    MAIN_MENU_EXIT_NEW_GAME,
    MAIN_MENU_EXIT_CONTINUE,
    MAIN_MENU_EXIT_INSTRUCTION,
    MAIN_MENU_EXIT_HIGH_SCORE,
    MAIN_MENU_EXIT_QUIT
};

const std::string GAME_LOGO_PATH = "./img/menu_logo.png";
const int GAME_LOGO_RENDER_POS_X = 100;
const int GAME_LOGO_RENDER_POS_Y = 100;
const int GAME_LOGO_RENDER_STRETCH = 2;

const int DECOR_BALL_RENDER_POS_X = 200;
const int DECOR_BALL_RENDER_POS_Y = 480;
const int DECOR_BALL_RENDER_STRETCH = 2;

const std::string NEW_GAME_BUTTON_TEXT = "NEW GAME";
const int NEW_GAME_BUTTON_RENDER_POS_X = 600;
const int NEW_GAME_BUTTON_RENDER_POS_Y = 280;

const std::string CONTINUE_BUTTON_TEXT = "CONTINUE";
const int CONTINUE_BUTTON_RENDER_POS_X = 930;
const int CONTINUE_BUTTON_RENDER_POS_Y = 280;

const std::string INSTRUCTION_BUTTON_TEXT = "INSTRUCTION";
const int INSTRUCTION_BUTTON_RENDER_POS_X = 600;
const int INSTRUCTION_BUTTON_RENDER_POS_Y = 400;

const std::string HIGH_SCORE_BUTTON_TEXT = "HIGH SCORE";
const int HIGH_SCORE_BUTTON_RENDER_POS_X = 930;
const int HIGH_SCORE_BUTTON_RENDER_POS_Y = 400;

class mainMenu
{
private:
    SDL_Renderer* mRenderer;
    
    LTexture mBackgroundTexture;

    LTexture mGameLogoTexture;  

    LTexture mSpritesheet;  

    redButton mNewGameButton;

    redButton mContinueButton;

    redButton mHighScoreButton;

    redButton mInstructionButton;

    highScoreMenu mHighScoreMenu;

    instructionMenu mInstructionMenu;

public:
    mainMenu();
    ~mainMenu();

    mainMenu(SDL_Renderer* __Renderer);

    void init(SDL_Renderer* __Renderer);

    MAIN_MENU_EXIT_STATUS render();
};

#endif