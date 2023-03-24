//game.h
#ifndef GAME_GUARD
#define GAME_GUARD

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sdl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "base.h"
#include "mainMenu.h"
#include "playLevel.h"

/**
 * @brief This file will control the working logic of the game, like starting page, levels
 * 
 */

class game
{
    private:
        /// @brief The window
        SDL_Window* mWindow;

        /// @brief The renderer
        SDL_Renderer* mRenderer;

        /// @brief The spritesheet of the game
        LTexture mSpritesheet;

        /// @brief The encoded map of all levels, loaded from config file
        vector_2d_string allLevelCharMap;
        
        /// @brief Moving range of all spiders in all levels
        vector_2d_spiderInfo allLevelSpidersInfo;

        /// @brief The starting size of the ball when being spawned
        std::vector <int> allLevelBallSpawnSize;
    
    public: 
        /// @brief Constructor
        game();

        /// @brief Destructor
        ~game();

        /// @brief Initialize SDL window, renderer, image
        /// @return 1 if successful, 0 otherwise
        bool initSDL();

        /// @brief Load data from config file
        void initMapConfig();

        /// @brief Settings before playing the game
        void preset();

        int getLastLevel() const;

        void updateLastLevel(const int& lastLevel);

        /// @brief The main gameplay
        void play();

        /// @brief Cleanup
        void clear();
};

#endif