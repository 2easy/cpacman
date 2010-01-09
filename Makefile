CFLAGS= `sdl-config --cflags`
pacman: main.o sound.o video.o engine.o
	gcc -lm `sdl-config --libs` main.o sound.o video.o engine.o -o pacman
