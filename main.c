#include<SDL.h>
#include"SDL_audio.h"
#include"sound.h"
#include"constants.h"
#include"video.h"
#include"main.h"

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

	pacman_direction = LEFT;
	int direction = NONE;
	int right_pressed = 0;
	int left_pressed = 0;
	int up_pressed = 0;
	int down_pressed = 0;
	while(!done)
	{
		int i;
		for (i=0;i< PACMAN_SPEED;i++) {
			move_pacman(direction);
		}
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
						right_pressed = 1;
						break;
					case SDLK_LEFT:
						left_pressed = 1;
						break;
					case SDLK_UP:
						up_pressed = 1;
						break;
					case SDLK_DOWN:
						down_pressed = 1;
						break;
					case SDLK_ESCAPE:
						done = 1;
						break;
				}
			} else if (event.type == SDL_KEYUP) {
				switch (event.key.keysym.sym)
				{
					case SDLK_RIGHT:
						right_pressed = 0;
						break;
					case SDLK_LEFT:
						left_pressed = 0;
						break;
					case SDLK_UP:
						up_pressed = 0;
						break;
					case SDLK_DOWN:
						down_pressed = 0;
						break;
				}
			}
		}
		if (right_pressed) direction = RIGHT;
		else if (left_pressed) direction = LEFT;
		else if (up_pressed) direction = UP;
		else if (down_pressed) direction = DOWN;
		else direction = NONE;
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
