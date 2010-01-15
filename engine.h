#ifndef ENGINE_H

#define ENGINE_H

#include<SDL.h>
extern SDL_Event event;
/*Map declaration*/
extern int map[31][30];
extern int n, m, have_powerup;

typedef struct {
	SDL_Rect animation[5];
	SDL_Rect position;
	int direction;
	int animation_state;
	int speed;
	int slow;
} pacman_t;

typedef struct {
	SDL_Rect animation[2];
	int image;
	SDL_Rect position;
	int speed;
	int direction;
	int animation_state;
	int weakness_state;
	int time_to_recover;
} ghost_t;

int menu(void);
void map_init(int map[31][30]);
void characters_init(pacman_t *pacman, ghost_t *ghosts, int *direction, SDL_Rect *background_dest);
void bring_ghosts_morale_back(ghost_t *ghosts);
void move_pacman(pacman_t *pacman, int direction, int * score);
int allot_direction(ghost_t *ghost); 
int get_direction_towards(ghost_t *ghost, int n, int m); 
void move_ghost(ghost_t *ghost, int ghost_name, pacman_t *pacman); 
void move_Ghost(ghost_t *ghost,pacman_t *pacman);
void chase_pacman(ghost_t *ghost, pacman_t *pacman);
int ghosts_collision(pacman_t *pacman, ghost_t *ghosts);
int pills_left(void);
void set_start_position(SDL_Rect * name_destination, int n, int m);
void set_all_start_positions(pacman_t *pacman, ghost_t *ghosts, SDL_Rect * background_dest);
unsigned int high_score (unsigned int score); 

#endif
