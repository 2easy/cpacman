#ifndef ENGINE_H

#define ENGINE_H

#include<SDL.h>
extern SDL_Event event;
/*Map declaration*/
extern int map[31][30];
extern int n, m, done;

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
	int weakness_state;
} ghost_t;

void map_init(int map[31][30]);
void characters_init(pacman_t *pacman, ghost_t *ghosts, int *direction, int *caught, SDL_Rect *background_dest);
void move_pacman(pacman_t *pacman,int direction);
void move_ghosts(ghost_t *ghost,pacman_t *pacman);
int ghosts_collision(pacman_t *pacman, ghost_t *ghosts);
int pills_left(void);
static void set_start_position(SDL_Rect * name_destination, int n, int m);
void set_all_start_positions(pacman_t *pacman, ghost_t *ghosts, SDL_Rect * background_dest);

#endif
