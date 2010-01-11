#include <SDL.h>
#include "SDL_audio.h"
#include "sound.h"
#include "constants.h"
#include "video.h"
#include "main.h"
#include "engine.h"

int main(int argc, char *args[])
{
	Uint8 * keystate = SDL_GetKeyState(NULL);
	pacman_t pacman;
	ghost_t ghosts[4];
	int i;
	srand(time(NULL));
	/*SDL initialization*/
	if ((screen = SDL_SetVideoMode(900,775,32,SDL_SWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN)) == NULL)
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
	/*Bitmaps initialization*/
	load_bitmaps();
	/*Cutting bitmaps to rectangles arrays*/
	init_bitmap_rect(pacman.animation, &pacman.position, 5);
	init_bitmap_rect(ghosts[0].animation, &ghosts[0].position, 2);
	init_bitmap_rect(ghosts[1].animation, &ghosts[1].position, 2);
	init_bitmap_rect(ghosts[2].animation, &ghosts[2].position, 2);
	init_bitmap_rect(ghosts[3].animation, &ghosts[3].position, 2);
	init_bitmap_rect(ground, &background_dest, 3);
	/*Characters initialization*/
	for (i=0;i<4;i++) {
		ghosts[i].animation_state = 0;
		ghosts[i].direction = LEFT;
		ghosts[i].image = i;
	}
	pacman.animation_state = 4 * PACMAN_ANIMATION_SPEED;
	pacman.direction = LEFT;
	int direction = NONE;
	set_all_start_positions(&pacman, ghosts, &background_dest);
	/*Last preparations*/
	int caught = NOT_CAUGHT;
	int lifes_left = PACMAN_MAX_LIFES;
	/*Let's the game begin*/
	while(!done)
	{
		int i;
		for (i=0;i< PACMAN_SPEED;i++) {
			move_pacman(&pacman,direction);
		}
		for (i=0;i< GHOST_SPEED;i++) {
			move_ghosts(ghosts, &pacman);
		}
		caught = ghosts_collision(&pacman, ghosts);
		if (caught) {
			if (!lifes_left) {
				printf("Game over.\n");
				exit(0);
			}
			set_all_start_positions(&pacman, ghosts, &background_dest);
			pacman.direction = LEFT;
			pacman.animation_state = 4 * PACMAN_ANIMATION_SPEED;
			direction = NONE;
			caught = NOT_CAUGHT;
			lifes_left--;
			draw(&pacman, ghosts);
			SDL_Flip(screen);
			SDL_Delay(1000);
		}		
		pills_left();
		draw(&pacman, ghosts);
		SDL_Flip(screen);
		while(SDL_PollEvent(&event))
		{
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
	/*---------------------------*/
	SDL_Quit();
	return 0;
}
