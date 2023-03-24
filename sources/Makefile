OBJS = main.cpp game.cpp base.cpp playLevel.cpp ball.cpp levelMap.cpp checkpoint.cpp spike.cpp portal.cpp brickTile.cpp finishLine.cpp lifeball.cpp pump.cpp shrinker.cpp spider.cpp trampolineTile.cpp waterloggedTile.cpp accelerator.cpp slopeTile.cpp mainMenu.cpp buttons.cpp miniMenu.cpp

CC = g++ -std=c++17

INCLUDE_PATHS = -IC:\MinGW32\include\SDL2

LIBRARY_PATHS = -LC:\MinGW32\lib

COMPILER_FLAG = -Wall -w -Wl,-subsystem,windows

LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

OBJ_NAME = ..\bounce.exe

all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAG) $(LINKER_FLAGS) -o $(OBJ_NAME)