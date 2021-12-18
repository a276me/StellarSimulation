SRCS = $(wildcard *.cpp)

default:
	g++ -o game $(SRCS) -Wall -std=c++17 -D_DEFAULT_SOURCE -Wno-missing-braces -s -O1 ./src/raylib.rc.data -Wl,--subsystem,windows -I. -I./src -I./src/external -I./include/ -L. -L./src -L./src -lraylib -lopengl32 -lgdi32 -lwinmm -DPLATFORM_DESKTOP
	game
