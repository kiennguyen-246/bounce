// base.cpp
#include "base.h"

using std::cout;

LTexture::LTexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    clear();
}

int LTexture::getWidth() const
{
    return mWidth;
}

int LTexture::getHeight() const
{
    return mHeight;
}

bool LTexture::loadTexture(SDL_Renderer* gRenderer, const char* path, const SDL_Color& colorKey)
{
    clear();
    
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL)
    {
        cout << "Unable to load " << path << ". Error: " << IMG_GetError() << ".\n";
        return 0;
    }
    else
    {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, colorKey.r, colorKey.g, colorKey.b));
        
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL)
        {
            cout << "Unable to create texture from " << path << ". Error: " << SDL_GetError()<< "\n";
            return 0;
        }
        else
        {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    
    mTexture = newTexture;
    return 1;
}

bool LTexture::loadTexture(SDL_Renderer* mRenderer, TTF_Font* mFont, const char* text, const SDL_Color& textColor)
{
	clear();

	SDL_Texture* newTexture = NULL;
	SDL_Surface* textSurface = TTF_RenderText_Solid(mFont, text, textColor);
    if (textSurface == NULL)
    {
        cout << "Unable to render text. Error code: " << TTF_GetError() << ".\n";
        return 0;
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
        if (newTexture == NULL)
        {
            cout << "Unable to create texture from given text. Error code: " << SDL_GetError()<< "\n";
            return 0;
        }
        else
        {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }
    
    mTexture = newTexture;
    return 1;

}

void LTexture::render(SDL_Renderer* mRenderer, const int& x, const int& y, SDL_Rect* clip, const int& stretchSize,
                     const double& angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    if (clip != NULL)
    {
        renderQuad.h = clip->h;
        renderQuad.w = clip->w;
    }

    renderQuad.h *= stretchSize;
    renderQuad.w *= stretchSize;

    if (x <= -1e6) renderQuad.x = (SCREEN_WIDTH - renderQuad.w) / 2;
    if (y <= -1e6) renderQuad.y = (SCREEN_HEIGHT - renderQuad.h) / 2;

    SDL_RenderCopyEx(mRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

void LTexture::clear()
{
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = mHeight = 0;
    }
}

gameObject::gameObject()
{

}

gameObject::~gameObject()
{

}

void gameObject::setPos(const int& x, const int& y)
{
    mPosX = x;
    mPosY = y;
}

void gameObject::setPos(const std::pair <int, int>& __Pos)
{
    setPos(__Pos.first, __Pos.second);
}

void gameObject::setSize(const int& w, const int& h)
{
    mWidth = w;
    mHeight = h;
}

int gameObject::getPosX() const
{
    return mPosX;
}

int gameObject::getPosY() const
{
    return mPosY;
}

void gameObject::setSpriteClip(LTexture& spritesheet, const int& x, const int& y, const int& w, const int& h) 
{
    mSpriteClip = {x, y, w, h};
}

SDL_Rect* gameObject::getSpriteClipPtr()
{
    return &mSpriteClip;
}

bool collide(const gameObject& obj1, const gameObject& obj2)
{
    int hitbox1L = obj1.mPosX;
    int hitbox1R = obj1.mPosX + obj1.mWidth;
    int hitbox1D = obj1.mPosY;
    int hitbox1U = obj1.mPosY - obj1.mHeight;

    int hitbox2L = obj2.mPosX;
    int hitbox2R = obj2.mPosX + obj2.mWidth;
    int hitbox2D = obj2.mPosY;
    int hitbox2U = obj2.mPosY - obj2.mHeight;

    // std::cout << "Size comparison: " << hitbox1R - hitbox1L + hitbox2R - hitbox2L << " " << std::max(hitbox1R, hitbox2R) - std::min(hitbox1L, hitbox2L) << "\n";

    if (((hitbox1R - hitbox1L + hitbox2R - hitbox2L) - (std::max(hitbox1R, hitbox2R) - std::min(hitbox1L, hitbox2L)) > 0) && 
        ((hitbox1D - hitbox1U + hitbox2D - hitbox2U) - (std::max(hitbox1D, hitbox2D) - std::min(hitbox1U, hitbox2U)) > 0)) return 1;
    return 0;
}

void renderText(SDL_Renderer* renderer, LTexture& texture, const char* text, const int& x, const int& y, 
                      const int& fontSize, const char* fontPath, const SDL_Color& fontColor)
{
    TTF_Font* font = TTF_OpenFont(fontPath, fontSize);

    if (!texture.loadTexture(renderer, font, text, fontColor)) 
    {
        cout << "Cannot render given text.\n";
    }
    else
    {
        texture.render(renderer, x, y);
    }
    TTF_CloseFont(font);
}