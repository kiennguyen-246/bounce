OBJS = main.cpp game.cpp base.cpp playLevel.cpp ball.cpp levelMap.cpp checkpoint.cpp spike.cpp portal.cpp brickTile.cpp finishLine.cpp lifeBall.cpp pump.cpp shrinker.cpp spider.cpp trampolineTile.cpp waterloggedTile.cpp accelerator.cpp slopeTile.cpp mainMenu.cpp buttons.cpp miniMenu.cpp

CC = g++ -std=c++17

#Modify the directory if Windows, comment if Linux
INCLUDE_PATHS = -IC:\MinGW32\include\SDL2

#Modify the directory if Windows, comment if Linux
LIBRARY_PATHS = -LC:\MinGW32\lib

#Windows
COMPILER_FLAG = -w -Wl,-subsystem,windows
#Linux
#COMPILER_FLAG = -w

#Windows
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
#Linux
#LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

#Windows
OBJ_NAME = ..\bounce.exe
#Linux
#OBJ_NAME = ..\bounce.exe

all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAG) $(LINKER_FLAGS) -o $(OBJ_NAME)