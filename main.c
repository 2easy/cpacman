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
	for (i=0;i<4;i++) {
		ghosts[i].animation_state = 0;
		ghosts[i].direction = LEFT;
	}
	pacman.animation_state = 0;
	/*SDL initialization*/
//SDL_FULLSCREEN
	if ((screen = SDL_SetVideoMode(750,775,32,SDL_SWSURFACE)) == NULL)
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
	init_bitmap_rect(pacman.animation, &pacman.position, 23, 15, 5);
	init_bitmap_rect(ghosts[0].animation, &ghosts[0].position, 11, 15, 2);
	/*init_bitmap_rect(inky, &inky_position, 14, 13, 4);
	init_bitmap_rect(pinky, &pinky_position, 14, 14, 4);
	init_bitmap_rect(clyde, &clyde_position, 14, 15, 4);
	init_bitmap_rect(confused, &clyde_position, 14, 15, 2);*/

	init_bitmap_rect(ground, &background_dest, 0, 1, 3);

	pacman.direction = LEFT;
	int direction = NONE;
	int right_pressed = 0;
	int left_pressed = 0;
	int up_pressed = 0;
	int down_pressed = 0;
	while(!done)
	{
		int i;
		for (i=0;i< PACMAN_SPEED;i++) {
			move_pacman(&pacman,direction);
		}
		draw(&pacman,ghosts);
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
		SDL_Flip(screen);
	}
	/*Freeing sounds*/
	SDL_FreeWAV(wave.sound);
	/*Freeing surfaces*/
	/*---------------------------*/
	SDL_Quit();
	return 0;
}
