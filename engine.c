#include "engine.h"

void move(int n1, int m1, int direction, SDL_Surface *pacman_sth_pic)
{
	switch (map[n1][m1])
	{

		case 1:
			switch (direction)
			{
				case 1:
					pacman_position.x += 25;
					previous_direction = 1;
					break;
				case 2:
					pacman_position.x -= 25;
					previous_direction = 2;
					break;
				case 3:
					pacman_position.y -=25;
					previous_direction = 3;
					break;
				case 4:
					pacman_position.y +=25;
					previous_direction = 4;
					break;
			}
			map[n][m] = 1;
			map[n1][m1] = 80;
			SDL_BlitSurface(ground_pic, &ground[00], screen, &background_dest);
				break;
		case 2:
			switch (direction)
			{
				case 1:
					pacman_position.x += 25;
					break;
				case 2:
					pacman_position.x -= 25;
					break;
				case 3:
					pacman_position.y -=25;
					break;
				case 4:
					pacman_position.y +=25;
			}
			map[n][m] = 1;
			map[n1][m1] = 80;
			SDL_BlitSurface(ground_pic, &ground[00], screen, &background_dest);
			break;
		case 3:
			switch (direction)
			{
				case 1:
					pacman_position.x += 25;
					break;
				case 2:
					pacman_position.x -= 25;
					break;
				case 3:
					pacman_position.y -=25;
					break;
				case 4:
					pacman_position.y +=25;
			}
			map[n][m] = 1;
			map[n1][m1] = 80;
			SDL_BlitSurface(ground_pic, &ground[00], screen, &background_dest);
			break;
		case 4:
			map[n][m] = 1;
			if (m1 = 29)
			{
				map[14][1] = 80;
				pacman_position.x = 25;
			}
			else
			{
				map[14][28] = 80;
				pacman_position.x = 700;
			}
			SDL_BlitSurface(ground_pic, &ground[00], screen, &background_dest);
			break;
		case 9:
			done = 1;
			break;
		default:
			if (previous_direction == direction)
				if (++state < 5)
					SDL_BlitSurface(pacman_sth_pic, &pacman[state], screen, &pacman_position);
				else
				{
					SDL_BlitSurface(pacman_sth_pic, &pacman[9-state], screen, &pacman_position);
					if (state == 9)
						state = 0;
				}
	}
}
