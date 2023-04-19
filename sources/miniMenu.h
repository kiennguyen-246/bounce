// miniMenu.h

#ifndef MINIMENU_GUARD
#define MINIMENU_GUARD

#include "base.h"
#include "buttons.h"

const int MINI_MENU_RENDER_POS_X = 160;
const int MINI_MENU_RENDER_POS_Y = 40;
const int MINI_MENU_WIDTH = 960;
const int MINI_MENU_HEIGHT = 560;

const std::string GAME_OVER_PROMPT[] = 
{
    "Unfortunately, you have no lives left. :(",
    "Astounding! You cleared all the levels! ^_^"
};

const std::string YELLOW_SAD_EMOJI_PATH = "./img/yellowSad.png";
const std::string YELLOW_SUNGLASSES_EMOJI_PATH = "./img/yellowSunglasses.png";
const std::string YELLOW_NERD_EMOJI_PATH = "./img/yellowNerd.png";
const std::string INSTRUCTION_MENU_IMAGES_PATH[] =
{
    "",
    "./img/instruction_moveLeftRight.png",
    "./img/instruction_jump.png",
    "./img/instruction_portal.png",
    "./img/instruction_spike.png",
    "./img/instruction_checkpoint.png",
    "./img/instruction_largeBall.png",
    "./img/instruction_special.png",
};

enum GAME_OVER_MENU_EXIT_STATUS
{
    GAME_OVER_EXIT_NULL,
    GAME_OVER_EXIT_REPLAY,
    GAME_OVER_EXIT_MAIN_MENU,
};
const int GAME_OVER_PROMPT_RENDER_POS_X = -1e6;
const int GAME_OVER_PROMPT_RENDER_POS_Y = 70;
const int GAME_OVER_PROMPT_FONT_SIZE = 36;
const int GAME_OVER_PROMPT_FONT_SIZE_LARGE = 48;
const std::string MAIN_MENU_BUTTON_TEXT = "MAIN MENU";
const int MAIN_MENU_BUTTON_RENDER_POS_X = 317;
const int MAIN_MENU_BUTTON_RENDER_POS_Y = 480;
const std::string REPLAY_BUTTON_TEXT = "REPLAY LEVEL";
const int REPLAY_BUTTON_RENDER_POS_X = 740;
const int REPLAY_BUTTON_RENDER_POS_Y = 480;

enum PAUSE_MENU_EXIT_STATUS
{
    PAUSE_EXIT_NULL,
    PAUSE_EXIT_RESUME,
    PAUSE_EXIT_MAIN_MENU,
    PAUSE_EXIT_ENTER_CHEAT_CODE
};
const int PAUSE_PROMPT_RENDER_POS_X = -1e6;
const int PAUSE_PROMPT_RENDER_POS_Y = 70;
const int PAUSE_PROMPT_FONT_SIZE = 72;
const std::string RESUME_BUTTON_TEXT = "RESUME";
const int RESUME_BUTTON_RENDER_POS_X = 317;
const int RESUME_BUTTON_RENDER_POS_Y = 480;
const std::string MAIN_MENU_2_BUTTON_TEXT = "MAIN MENU";
const int MAIN_MENU_2_BUTTON_RENDER_POS_X = 740;
const int MAIN_MENU_2_BUTTON_RENDER_POS_Y = 480;

enum HIGH_SCORE_MENU_EXIT_STATUS
{
    HIGH_SCORE_EXIT_NULL,
    HIGH_SCORE_EXIT_RETURN
};
const int HIGH_SCORE_PROMPT_RENDER_POS_X = -1e6;
const int HIGH_SCORE_PROMPT_RENDER_POS_Y = 70;
const int HIGH_SCORE_PROMPT_FONT_SIZE = 60;
const int HIGH_SCORE_PROMPT_FONT_SIZE_LARGE = 72;
const std::string RETURN_BUTTON_TEXT = "RETURN";
const int RETURN_BUTTON_RENDER_POS_X = 520;
const int RETURN_BUTTON_RENDER_POS_Y = 500;

enum INSTRUCTION_MENU_EXIT_STATUS
{
    INSTRUCTION_EXIT_NULL,
    INSTRUCTION_EXIT_RETURN,
    INSTRUCTION_EXIT_PREVIOUS,
    INSTRUCTION_EXIT_NEXT,
};
const int INSTRUCTION_TEXT_RENDER_POS_X = 200;
const int INSTRUCTION_TITLE_RENDER_POS_X = -1e6;
const int INSTRUCTION_TITLE_RENDER_POS_Y = 70;
const int INSTRUCTION_TEXT_FONT_SIZE = 30;
const int INSTRUCTION_TITLE_FONT_SIZE = 60;
const std::string PREVIOUS_BUTTON_TEXT = "<< PREVIOUS";
const int PREVIOUS_BUTTON_RENDER_POS_X = 186;
const int PREVIOUS_BUTTON_RENDER_POS_Y = 500;
const std::string NEXT_BUTTON_TEXT = "NEXT >>";
const int NEXT_BUTTON_RENDER_POS_X = 838;
const int NEXT_BUTTON_RENDER_POS_Y = 500;
const int INSTRUCTION_MENU_PAGE_COUNT = 7;

int getHighScore();

void reloadHighScore(const int& newScore);

class miniMenu
{
protected:
    SDL_Rect mContainer;
public:
    miniMenu(/* args */);
    ~miniMenu();

    virtual void render(SDL_Renderer* renderer) = 0;
};

class gameOverMenu: public miniMenu
{
private:
    bool isVictory;

    LTexture mYellowSad;
    LTexture mYellowSunglasses;

    int mScore;

    redButton mMainMenuButton, mReplayButton;
public:
    gameOverMenu();
    ~gameOverMenu();

    bool checkIsVictory() const;

    void set(SDL_Renderer* renderer);

    void handleEvent(SDL_Event* event, GAME_OVER_MENU_EXIT_STATUS& exitStatus);

    void setVictory(const bool& __isVivtory);

    void setScore(const int& __score);

    void render(SDL_Renderer* renderer);
};


class highScoreMenu: public miniMenu
{
private:    
    redButton mReturnButton;

    LTexture mYellowSunglasses;

public:
    highScoreMenu();
    ~highScoreMenu();

    void set(SDL_Renderer* renderer);

    void handleEvent(SDL_Event* event, HIGH_SCORE_MENU_EXIT_STATUS& exitStatus);

    void render(SDL_Renderer* renderer);
};

class pauseMenu: public miniMenu
{
private:    
    redButton mResumeButton;
    redButton mMainMenuButton;

    LTexture mYellowNerd;

public:
    pauseMenu();
    ~pauseMenu();

    void set(SDL_Renderer* renderer);

    void handleEvent(SDL_Event* event, PAUSE_MENU_EXIT_STATUS& exitStatus);

    void render(SDL_Renderer* renderer);
};

class instructionMenu: public miniMenu
{
private:
    std::vector <std::vector <std::string> > mInstructionText;

    int pageId;

    redButton mReturnButton;
    redButton mPreviousButton;
    redButton mNextButton;

    LTexture mImage;

public:
    instructionMenu();
    ~instructionMenu();

    void loadInstructionText();

    void set(SDL_Renderer* renderer, const int& pageId);

    void nextPage(SDL_Renderer* renderer);

    void previousPage(SDL_Renderer* renderer);

    void handleEvent(SDL_Event* event, INSTRUCTION_MENU_EXIT_STATUS& exitStatus);

    void render(SDL_Renderer* renderer);
};
#endif

