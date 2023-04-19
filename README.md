# Bounce Classic Remake
Version: 1.2

## Overview
Have you ever played this legendary game on Nokia 1280? 

![nokia 1280 image](https://github.com/kiennguyen2464/bounce/blob/main/img/bounceNokia1280.jpg?raw=true)

(image found randomly on Google)

This "Bounce" game that I made is a remake of this, using the texture for a more modern version. Due to my preference, I tried to make it as much similar to
the Nokia 1280 version as possible. You may find that the ball does not spin, or the gameplay frame does not move with the ball.

Also, because of the lack of resources, I cannot add any appropriate soundtrack to the game. The game also have only 4 levels, with some minor differences to the original
game.

Hope this low-cost SDL remake will somehow bring you back to that memory. (of course only if you have played this game before)

## Installing

**Step 1**: Install [`Mingw-w64`](https://sourceforge.net/projects/mingw-w64/files/). While this game was being made, we used `GCC-7.3.0 i686-posix-sjlj`.

- If you have used any version of MinGW32 before, skip this step

**Step 2**: My game runs on SDL. Therefore, to play the game, please install 
[`SDL2`](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/mingw/index.php),
[`SDL2_mixer`](https://github.com/libsdl-org/SDL_mixer/releases), 
[`SDL2_image`](https://github.com/libsdl-org/SDL_image/releases/tag/release-2.6.3), 
[`SDL2_ttf`](https://github.com/libsdl-org/SDL_ttf/releases/tag/release-2.20.2). 

- Follow the [Lazyfoo's instruction](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php) to install those more easily.

- Edit sources/Makefile based on the suggestions.

**Step 3**: Install [`GNU MAKE`](https://stackoverflow.com/a/57042516/21271990).

- If you have used mingw-make before or having Codeblocks with MinGW32 setup, skip this step.

**Step 4**: Clone this repo. Change directory to `sources` and use the command `mingw32-make` (Windows) or `make` (Linux)

- You may use `installer.bat` (Windows only) to quickly setup the game.

**Step 5**: Enjoy the game. 

![thumbs up](https://github.com/kiennguyen2464/bounce/blob/main/img/yellowSunglasses.png?raw=true)

## Credits

Most of the source code for the game was created by me - kiennguyen246 (because I was boring and have a lot of spare time 😅).

To view my detailed progress to develop this game, visit my [practice repo folder](https://github.com/kiennguyen2464/learnSDL/tree/main/bounce).

Special thanks to [anish-g](https://github.com/anish-g) for the game assets.
