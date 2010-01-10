#ifndef ENGINE_H

#define ENGINE_H

#include<SDL.h>
extern SDL_Event event;
/*Rectangles declarations*/
/*Map declaration*/
extern int map[31][30];
extern int n, m, done, state;

typedef struct {
	SDL_Rect animation[5];
	SDL_Rect position;
	int direction;
	int animation_state;
} pacman_t;

typedef struct {
	SDL_Rect animation[2];
	int image;
	SDL_Rect position;
	int direction;
	int animation_state;
} ghost_t;

void move_pacman(pacman_t *pacman,int direction);
void move_ghost(ghost_t *ghost);

#endif
