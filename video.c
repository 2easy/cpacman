#include"video.h"

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
	name_destination->x = m * 25;
	name_destination->y = n * 25;
	name_destination->h = 25;
	name_destination->w = 25;
	/*cutting ghost to the array*/
	for (i = 0; i < quantity; i++)
	{
		name[i].h = 25;
		name[i].w = 25;
	}
	for (i = 0; i < quantity; i++)
	{
		name[i].x = j;
		name[i].y = 0;
		j += 25;
	}
	return 0;
}
