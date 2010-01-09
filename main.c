#include<SDL.h>
#include "SDL_audio.h"
#include "sound.h"
#include "constants.h"
#include "video.h"
/*Surfaces declarations*/
SDL_Surface *screen = NULL;
SDL_Surface *blinky_pic, *inky_pic, *pinky_pic, *clyde_pic, *confused_pic;
SDL_Surface *pacman_up_pic, *pacman_down_pic, *pacman_right_pic, *pacman_left_pic;
SDL_Surface *ground_pic;
SDL_Surface *map_pic;
SDL_Event event;
/*Rectangles declarations*/
SDL_Rect blinky[4], inky[4], pinky[4], clyde[4], confused[2];
SDL_Rect blinky_position, inky_position, pinky_position, clyde_position;
SDL_Rect pacman[5], pacman_position;
int pacman_direction;
SDL_Rect ground[3], background_dest;
/*--------------------------Map initialization-------------------------------*/
/*------0 -> wall, 1 -> ground, 2 -> pill, 3 ->super pill, 4 -> teleport----*/
int map[31][30] =
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	, 0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,0
	, 0,0,2,0,0,0,0,2,0,0,0,0,0,2,0,0,2,0,0,0,0,0,2,0,0,0,0,2,0,0
	, 0,0,3,0,0,0,0,2,0,0,0,0,0,2,0,0,2,0,0,0,0,0,2,0,0,0,0,3,0,0
	, 0,0,2,0,0,0,0,2,0,0,0,0,0,2,0,0,2,0,0,0,0,0,2,0,0,0,0,2,0,0
	, 0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0
	, 0,0,2,0,0,0,0,2,0,0,2,0,0,0,0,0,0,0,0,2,0,0,2,0,0,0,0,2,0,0
	, 0,0,2,0,0,0,0,2,0,0,2,0,0,0,0,0,0,0,0,2,0,0,2,0,0,0,0,2,0,0
	, 0,0,2,2,2,2,2,2,0,0,2,2,2,2,0,0,2,2,2,2,0,0,2,2,2,2,2,2,0,0
	, 0,0,0,0,0,0,0,2,0,0,0,0,0,1,0,0,1,0,0,0,0,0,2,0,0,0,0,0,0,0
	, 0,0,0,0,0,0,0,2,0,0,0,0,0,1,0,0,1,0,0,0,0,0,2,0,0,0,0,0,0,0
	, 0,0,0,0,0,0,0,2,0,0,1,1,1,1,1,1,1,1,1,1,0,0,2,0,0,0,0,0,0,0
	, 0,0,0,0,0,0,0,2,0,0,1,0,0,0,5,5,0,0,0,1,0,0,2,0,0,0,0,0,0,0
	, 0,0,0,0,0,0,0,2,0,0,1,0,0,1,1,1,1,0,0,1,0,0,2,0,0,0,0,0,0,0
	, 4,1,1,1,1,1,1,2,1,1,1,0,0,1,1,1,1,0,0,1,1,1,2,1,1,1,1,1,1,4
	, 0,0,0,0,0,0,0,2,0,0,1,0,0,1,1,1,1,0,0,1,0,0,2,0,0,0,0,0,0,0
	, 0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0
	, 0,0,0,0,0,0,0,2,0,0,1,1,1,1,1,1,1,1,1,1,0,0,2,0,0,0,0,0,0,0
	, 0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0
	, 0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0
	, 0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,0
	, 0,0,2,0,0,0,0,2,0,0,0,0,0,2,0,0,2,0,0,0,0,0,2,0,0,0,0,2,0,0
	, 0,0,3,0,0,0,0,2,0,0,0,0,0,2,0,0,2,0,0,0,0,0,2,0,0,0,0,3,0,0
	, 0,0,2,2,2,0,0,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,0,0,2,2,2,0,0
	, 0,0,0,0,2,0,0,2,0,0,2,0,0,0,0,0,0,0,0,2,0,0,2,0,0,2,0,0,0,0
	, 0,0,0,0,2,0,0,2,0,0,2,0,0,0,0,0,0,0,0,2,0,0,2,0,0,2,0,0,0,0
	, 0,0,2,2,2,2,2,2,0,0,2,2,2,2,0,0,2,2,2,2,0,0,2,2,2,2,2,2,0,0
	, 0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0
	, 0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0
	, 0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0
	, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
/*----------------------------------------------------------------------------*/
int done = 0, n = 23, m = 15, state = 0;

void draw() {
	SDL_BlitSurface(map_pic, NULL, screen, &background_dest);
	draw_dots();
	SDL_BlitSurface(pacman_left_pic, &pacman[0], screen, &pacman_position);
}
int main(int argc, char *args[])
{
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
	pacman_up_pic = init_bitmap("pacman_up.bmp");
	pacman_down_pic = init_bitmap("pacman_down.bmp");
	pacman_right_pic = init_bitmap("pacman_right.bmp");
	pacman_left_pic = init_bitmap("pacman_left.bmp");
	blinky_pic = init_bitmap("ghost_blinky.bmp");
	inky_pic = init_bitmap("ghost_inky.bmp");
	pinky_pic = init_bitmap("ghost_pinky.bmp");
	clyde_pic = init_bitmap("ghost_clyde.bmp");
	confused_pic = init_bitmap("confused_ghost.bmp");
	ground_pic = init_bitmap("ground.bmp");
	/*Cutting bitmaps to rectangles arrays*/
	init_bitmap_rect(pacman, &pacman_position, 23, 15, 5);
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

	SDL_Flip(screen);
	/*map[11][15] = 9;
	map[14][13] = 9;
	map[14][14] = 9;
	map[14][15] = 9;*/
	pacman_direction = LEFT;
	int direction = NONE;
	while(!done)
	{
		move_pacman(direction);
		draw();
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
				done = 1;
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_RIGHT:
						direction = RIGHT;
						break;
					case SDLK_LEFT:
						direction = LEFT;
						break;
					case SDLK_UP:
						direction = UP;
						break;
					case SDLK_DOWN:
						direction = DOWN;
						break;
					case SDLK_ESCAPE:
						done = 1;
						break;
				}
			} else if (event.type == SDL_KEYUP) {
				direction = NONE;
			}
		}
		SDL_Flip(screen);
	}
	/*Freeing sounds*/
	SDL_FreeWAV(wave.sound);
	/*Freeing surfaces*/
	SDL_FreeSurface(map_pic);
	SDL_FreeSurface(pacman_up_pic);
	SDL_FreeSurface(pacman_down_pic);
	SDL_FreeSurface(pacman_right_pic);
	SDL_FreeSurface(pacman_left_pic);
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
