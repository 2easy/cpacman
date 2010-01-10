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
	map_pic = init_bitmap("map.bmp");
	pacman_pic[UP] = init_bitmap("pacman_up.bmp");
	pacman_pic[DOWN] = init_bitmap("pacman_down.bmp");
	pacman_pic[RIGHT] = init_bitmap("pacman_right.bmp");
	pacman_pic[LEFT] = init_bitmap("pacman_left.bmp");

	blinky_pic = init_bitmap("ghost_blinky.bmp");
	inky_pic = init_bitmap("ghost_inky.bmp");
	pinky_pic = init_bitmap("ghost_pinky.bmp");
	clyde_pic = init_bitmap("ghost_clyde.bmp");
	confused_pic = init_bitmap("confused_ghost.bmp");
	ground_pic = init_bitmap("ground.bmp");
	/*Cutting bitmaps to rectangles arrays*/
	init_bitmap_rect(pacman.animation, &pacman.position, 23, 15, 5);
	init_bitmap_rect(blinky, &blinky_position, 11, 15, 4);
	init_bitmap_rect(inky, &inky_position, 14, 13, 4);
	init_bitmap_rect(pinky, &pinky_position, 14, 14, 4);
	init_bitmap_rect(clyde, &clyde_position, 14, 15, 4);
	init_bitmap_rect(confused, &clyde_position, 14, 15, 2);
	init_bitmap_rect(ground, &background_dest, 0, 1, 3);
	/*Draw start positions*/
	/*
	SDL_BlitSurface(blinky_pic, &blinky[3], screen, &blinky_position);
	SDL_BlitSurface(inky_pic, &inky[1], screen, &inky_position);
	SDL_BlitSurface(pinky_pic, &pinky[1], screen, &pinky_position);
	SDL_BlitSurface(clyde_pic, &clyde[1], screen, &clyde_position);*/

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
		draw();
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
	SDL_FreeSurface(map_pic);
	SDL_FreeSurface(pacman_pic[LEFT]);
	SDL_FreeSurface(pacman_pic[RIGHT]);
	SDL_FreeSurface(pacman_pic[UP]);
	SDL_FreeSurface(pacman_pic[DOWN]);
	SDL_FreeSurface(blinky_pic);
	SDL_FreeSurface(inky_pic);
	SDL_FreeSurface(pinky_pic);
	SDL_FreeSurface(clyde_pic);
	SDL_FreeSurface(confused_pic);
	SDL_FreeSurface(ground_pic);
	/*---------------------------*/
	SDL_Quit();
	return 0;
}
