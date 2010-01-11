#include "video.h"
#include "engine.h"
#include "constants.h"

static SDL_Surface *ghost_pic[4][5];
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

int init_bitmap_rect(SDL_Rect * name, SDL_Rect * name_destination, int quantity)
{
	int i, j = 0;
	/*initializing destination rect*/
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

static void draw_dots(void)
{
	int i, j;
	SDL_Rect dot;
	for (i = 1; i < 30; i++) {
		for (j = 1; j < 28; j++) {
			dot.x = j * IMAGE_WIDTH;
			dot.y = i * IMAGE_HEIGHT;
			if (map[i][j] == PILL) {
				SDL_BlitSurface(ground_pic, &ground[0], screen, &dot);
			} else if (map[i][j] == POWERUP) {
				SDL_BlitSurface(ground_pic, &ground[1], screen, &dot);
			} else if (map[i][j] == CAGE) {
				SDL_BlitSurface(ground_pic, &ground[2], screen, &dot);
			}
		}
	}
}

static void draw_pacman(pacman_t* pacman) {
	int anim = (pacman->animation_state++) / PACMAN_ANIMATION_SPEED;
	if (anim == 7) pacman->animation_state = 0;
	if (anim > 4) anim = 8-anim;
	SDL_BlitSurface(pacman_pic[pacman->direction], &pacman->animation[anim], screen, &pacman->position);
}
static void draw_ghosts(ghost_t* ghosts) {
	int i, anim;

	for (i=0;i<4;i++) {
		anim = ((ghosts[i].animation_state++) / GHOST_ANIMATION_SPEED) % 2;
		SDL_BlitSurface(ghost_pic[i][ghosts[i].direction], &ghosts[i].animation[anim], screen, &ghosts[i].position);
	}
}
void draw(pacman_t *pacman,ghost_t* ghosts) {
	SDL_BlitSurface(map_pic, NULL, screen, &background_dest);
	draw_dots();
	draw_pacman(pacman);
	draw_ghosts(ghosts);
}
void load_bitmaps(void) {
	map_pic = init_bitmap("map.bmp");
	pacman_pic[UP] = init_bitmap("pacman_up.bmp");
	pacman_pic[DOWN] = init_bitmap("pacman_down.bmp");
	pacman_pic[RIGHT] = init_bitmap("pacman_right.bmp");
	pacman_pic[LEFT] = init_bitmap("pacman_left.bmp");
	
	ghost_pic[0][UP] = init_bitmap("blinky_up.bmp");
	ghost_pic[0][DOWN] = init_bitmap("blinky_down.bmp");
	ghost_pic[0][RIGHT] = init_bitmap("blinky_right.bmp");
	ghost_pic[0][LEFT] = init_bitmap("blinky_left.bmp");
	ghost_pic[1][UP] = init_bitmap("inky_up.bmp");
	ghost_pic[1][DOWN] = init_bitmap("inky_down.bmp");
	ghost_pic[1][RIGHT] = init_bitmap("inky_right.bmp");
	ghost_pic[1][LEFT] = init_bitmap("inky_left.bmp");
	ghost_pic[2][UP] = init_bitmap("pinky_up.bmp");
	ghost_pic[2][DOWN] = init_bitmap("pinky_down.bmp");
	ghost_pic[2][RIGHT] = init_bitmap("pinky_right.bmp");
	ghost_pic[2][LEFT] = init_bitmap("pinky_left.bmp");
	ghost_pic[3][UP] = init_bitmap("clyde_up.bmp");
	ghost_pic[3][DOWN] = init_bitmap("clyde_down.bmp");
	ghost_pic[3][RIGHT] = init_bitmap("clyde_right.bmp");
	ghost_pic[3][LEFT] = init_bitmap("clyde_left.bmp");

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
