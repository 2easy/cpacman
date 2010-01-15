#include <SDL.h>
#include "SDL_audio.h"
#include "sound.h"
#include "constants.h"
#include "video.h"
#include "engine.h"
/*Surfaces declarations*/
SDL_Surface *screen = NULL;
SDL_Event event;
/*Rectangles declarations*/
SDL_Rect ground[4], background_dest;
int map[31][30];
int done = 0, n = 23, m = 15, have_power = 0;

int main(int argc, char *args[])
{
	Uint8 * keystate = SDL_GetKeyState(NULL);
	pacman_t pacman;
	ghost_t ghosts[4];
	int i, j;
	srand(time(NULL));
	/*SDL initialization*/
	if ((screen = SDL_SetVideoMode(850,775,32,SDL_SWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN)) == NULL)
	{
		fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
		SDL_Quit();
		exit(1);
	}
	/*Menu*/
	map_init(map);
	/*Bitmaps initialization*/
	load_bitmaps();
	/*Cutting bitmaps to rectangles arrays*/
	init_bitmap_rect(pacman.animation, &pacman.position, 5);
	init_bitmap_rect(ghosts[0].animation, &ghosts[0].position, 2);
	init_bitmap_rect(ghosts[1].animation, &ghosts[1].position, 2);
	init_bitmap_rect(ghosts[2].animation, &ghosts[2].position, 2);
	init_bitmap_rect(ghosts[3].animation, &ghosts[3].position, 2);
	init_bitmap_rect(ground, &background_dest, 3);
	/*Last preparations*/
	int direction = NONE;
	int lifes_left = PACMAN_MAX_LIFES;
	unsigned int score = 0, level = 1;
	characters_init(&pacman, ghosts, &direction, &background_dest);
	/*Let's the game begin*/
	while(!done)
	{
		int i;
		int collision;
		int pacman_speed = PACMAN_SPEED;
		int ghosts_speed[4] = {GHOST_SPEED, GHOST_SPEED, GHOST_SPEED, GHOST_SPEED}; 
		/*Slow down eating pacman*/
		if (pacman.slow) {
			pacman.slow--;
			pacman_speed = PACMAN_SPEED - 1;
		}
		bring_ghosts_morale_back(ghosts);
		/*Weaken ghosts if got POWERUP*/
		if (have_power) {
			for (i = 0; i < 4; i++) {
				ghosts[i].weakness_state = WEAK;
				ghosts[i].time_to_recover = TIME_TO_RECOVER;
				have_power = 0;
			}
		}
		/*Move pacman*/
		for (i = 0; i < pacman_speed; i++) {
			move_pacman(&pacman, direction, &score);
		}
		/*Collision detection*/
		collision = ghosts_collision(&pacman, ghosts);
		if (collision != NOT_CAUGHT) {
			if (ghosts[collision].weakness_state != NORMAL) {
				set_start_position(&(ghosts[collision].position), 14, 14);
				ghosts[collision].weakness_state = NORMAL;
				score += 400;
			} else {
				lifes_left--;
				if (!lifes_left) {
					int best = hiscore(score);
					if (score == best) {
						printf("Congratulations! You have beaten hiscore!\nScore: %d\n", score);
					} else {
						printf("Game over. You need more practise.\nScore: %d\nHiscore: %d\n", score, best);
					}
					exit(0);
				}
				characters_init(&pacman, ghosts, &direction, &background_dest);
				draw(&pacman, ghosts);
				draw_lifes(&pacman, lifes_left);
				SDL_Flip(screen);
				SDL_Delay(1000);
			}
		}
		/*Slow the ghosts down if they are weak*/
		for (i = 0; i < 4; i++) {
			if (ghosts[i].weakness_state != NORMAL) {
				ghosts_speed[i] = GHOST_SPEED - 2;
			}
		}
		/*Move ghosts around*/	
		for (i = 0; i < 4; i++) {
			for (j = 0; j < ghosts_speed[i]; j++) {
				move_ghost(ghosts + i, &pacman);
			}
		}
		/*Next level*/
		if (!pills_left()) {
			level++;
			map_init(map);
			characters_init(&pacman, ghosts, &direction, &background_dest);
			draw(&pacman, ghosts);
			draw_lifes(&pacman, lifes_left);
			SDL_Flip(screen);
			SDL_Delay(1000);
		}
		draw(&pacman, ghosts);
		draw_lifes(&pacman, lifes_left);
		SDL_Flip(screen);
		/*Detecting player signals*/
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT)
				done = 1;
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
				done = 1;
		}
		if (keystate[SDLK_RIGHT]) {
			direction = RIGHT;
		} else if (keystate[SDLK_LEFT]) {
			direction = LEFT;
		} else if (keystate[SDLK_UP]) {
			direction = UP;
		} else if (keystate[SDLK_DOWN]) {
			direction = DOWN;
		} else {
			direction = NONE;
		}
	}
	/*Freeing sounds*/
	SDL_FreeWAV(wave.sound);
	/*Freeing surfaces*/
	free_surfaces();
	SDL_Quit();
	return 0;
}
