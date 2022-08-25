SRC_FILES = src/main.cpp
CC_FLAGS = -O2 -Wall -Wno-missing-braces -I include/ -L lib/ -l raylib -l opengl32 -l gdi32 -l winmm
CC = g++

all:
	$(CC) -o rayclick $(SRC_FILES) $(CC_FLAGS)