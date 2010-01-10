#include "video.h"
#include "engine.h"
#include "constants.h"

static SDL_Surface *blinky_pic[5];
static SDL_Surface *inky_pic[5];
static SDL_Surface *pinky_pic[5];
static SDL_Surface *clyde_pic[5];
static SDL_Surface *pacman_pic[5];
static SDL_Surface *ground_pic;
static SDL_Surface *map_pic;

SDL_Surface * init_bitmap(const char file_name[])
{
	SDL_Surface * tmp = NULL;

	if ((tmp = SDL_LoadBMP(file_name)) == NULL)
	{
		fprintf(stderr, "Couldn't open %s\n", file_name);
		exit(1);
	}
	return tmp;
}

int init_bitmap_rect(SDL_Rect * name, SDL_Rect * name_destination, int n, int m, int quantity)
{
	int i, j = 0;
	/*initializing destination rect*/
	name_destination->x = m * IMAGE_WIDTH;
	name_destination->y = n * IMAGE_HEIGHT;
	name_destination->h = IMAGE_HEIGHT;
	name_destination->w = IMAGE_WIDTH;
	/*cutting ghost to the array*/
	for (i = 0; i < quantity; i++)
	{
		name[i].h = IMAGE_HEIGHT;
		name[i].w = IMAGE_WIDTH;
	}
	for (i = 0; i < quantity; i++)
	{
		name[i].x = j;
		name[i].y = 0;
		j += IMAGE_WIDTH;
	}
	return 0;
}

void draw_dots(void)
{
	int i, j;
	SDL_Rect dot;
	for (i = 1; i < 30; i++)
		for (j = 1; j < 28; j++) {
			dot.x = j * IMAGE_WIDTH;
			dot.y = i * IMAGE_HEIGHT;
			if (map[i][j] == 1)
				SDL_BlitSurface(ground_pic, &ground[0], screen, &dot);
			if (map[i][j] == 2)
				SDL_BlitSurface(ground_pic, &ground[1], screen, &dot);
			if (map[i][j] == 3)
				SDL_BlitSurface(ground_pic, &ground[2], screen, &dot);
		}
}

void draw_pacman(pacman_t* pacman) {
	int anim = (pacman->animation_state++) / PACMAN_ANIMATION_SPEED;
	if (anim == 9) pacman->animation_state = 0;
	if (anim > 4) anim = 9-anim;
	SDL_BlitSurface(pacman_pic[pacman->direction], &pacman->animation[anim], screen, &pacman->position);
}
void draw(pacman_t *pacman) {
	SDL_BlitSurface(map_pic, NULL, screen, &background_dest);
	draw_dots();
	draw_pacman(pacman);
}
void load_bitmaps(void) {
	map_pic = init_bitmap("map.bmp");
	pacman_pic[UP] = init_bitmap("pacman_up.bmp");
	pacman_pic[DOWN] = init_bitmap("pacman_down.bmp");
	pacman_pic[RIGHT] = init_bitmap("pacman_right.bmp");
	pacman_pic[LEFT] = init_bitmap("pacman_left.bmp");
	
	blinky_pic[UP] = init_bitmap("blinky_up.bmp");
	blinky_pic[DOWN] = init_bitmap("blinky_down.bmp");
	blinky_pic[RIGHT] = init_bitmap("blinky_right.bmp");
	blinky_pic[LEFT] = init_bitmap("blinky_left.bmp");
	ground_pic = init_bitmap("ground.bmp");
}
void free_surface(void) {
	/*SDL_FreeSurface(map_pic);
	SDL_FreeSurface(pacman_pic[LEFT]);
	SDL_FreeSurface(pacman_pic[RIGHT]);
	SDL_FreeSurface(pacman_pic[UP]);
	SDL_FreeSurface(pacman_pic[DOWN]);
	SDL_FreeSurface(blinky_pic);
	SDL_FreeSurface(inky_pic);
	SDL_FreeSurface(pinky_pic);
	SDL_FreeSurface(clyde_pic);
	SDL_FreeSurface(confused_pic);
	SDL_FreeSurface(ground_pic);*/
}
