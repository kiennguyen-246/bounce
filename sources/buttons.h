// buttons.h

#ifndef BUTTONS_GUARD
#define BUTTONS_GUARD

#include "base.h"

const std::string RED_BUTTON_PATH = "./img/redButton.png";
const int RED_BUTTON_WIDTH = 267;
const int RED_BUTTON_HEIGHT = 75;
const int RED_BUTTON_STRETCH_SIZE = 1;
const int RED_BUTTON_TEXT_FONT_SIZE = 30;

const int BLUE_BUTTON_WIDTH = 75;
const int BLUE_BUTTON_HEIGHT = 75;
const int BLUE_BUTTON_STRETCH_SIZE = 1;

/// @brief Button class
class LButton
{
protected:
    /// @brief Upper left position of the button
    SDL_Point mPos;

    int mWidth;
    int mHeight;
    
    /// @brief The texture rendered with the button
    LTexture mButtonTexture;
    SDL_Rect* mSpriteClipPtr;

    /// @brief The text rendered inside the button
    std::string mText;
    LTexture mTextTexture;

    bool textIsSetUp;

public:
    /// @brief Constructor
    LButton();

    /// @brief Set the texture rendered with the button
    void setTexture(const LTexture& __Texture);

    /// @brief Set the text rendered inside the button
    void setText(SDL_Renderer* renderer, const std::string& __Text, const int& fontSize = 48, const char* fontPath = &CALIBRI_FONT_PATH[0], const SDL_Color& fontColor = SDL_COLOR_BLACK);

    /// @brief Set the upper left position, width and height of the button
    void set(const int& x, const int& y, const int& __w, const int& __h);
    
    /// @brief Set up a button with a given texture
    void set(const int& x, const int& y, const LTexture& __ButtonTexture);

    /// @brief Get the upper left position of the button
    SDL_Point getPos();
    /// @brief Get the width of the button
    int getWidth();

    /// @brief Get the height of the button
    int getHeight();

    /// @brief Render the button
    void render(SDL_Renderer* renderer);

    void handleEvent(SDL_Event* event, bool& isTriggered);
};

class redButton: public LButton
{
protected:

public:
    redButton();
    ~redButton();

    void set(SDL_Renderer* renderer, const int& x, const int& y, const std::string& text);
};

class blueButton: public LButton
{
protected:

public:
    blueButton();
    ~blueButton();

    void set(SDL_Renderer* renderer, const int& x, const int& y, const std::string& texturePath);
};

#endif