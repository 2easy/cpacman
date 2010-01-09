#include"video.h"
#include"constants.h"

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
	

