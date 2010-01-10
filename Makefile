%.o : %.c *.h
	gcc -g -c `sdl-config --cflags` $< -o $@
pacman: main.o sound.o video.o engine.o *.h
	gcc -lm `sdl-config --libs` main.o sound.o video.o engine.o -o pacman
