#include"engine.h"
#include"constants.h"

void move_pacman(int direction)
{
	if (pacman_position.x % 25 == 0 && pacman_position.y % 25 == 0 && direction) {
		pacman_direction = direction;
	}

	if (pacman_position.x % 25 == 0 && pacman_position.y % 25 == 0 && direction) {
		int x = pacman_position.x / IMAGE_HEIGHT;
		int y = pacman_position.y / IMAGE_WIDTH;
		switch (pacman_direction)
		{
			case RIGHT:
				x++;
				break;
			case LEFT:
				x--;
				break;
			case UP:
				y--;
				break;
			case DOWN:
				y++;
				break;
			default:
				printf("direction %d\n",direction);
				exit(0);
		}
		if (map[y][x] == EMPTY || map[y][x] == PILL) {
		} else {
			return;
		}
		
	}

	int next_x = pacman_position.x;
	int next_y = pacman_position.y;

	switch (pacman_direction)
	{
		case RIGHT:
			next_x += PACMAN_SPEED;
			break;
		case LEFT:
			next_x -= PACMAN_SPEED;
			break;
		case UP:
			next_y -= PACMAN_SPEED;
			break;
		case DOWN:
			next_y += PACMAN_SPEED;
			break;
		default:
			printf("direction %d\n",direction);
		 	exit(0);
	}
	pacman_position.x = next_x;
	pacman_position.y = next_y;

	/*int next = map[n1][m1];
	if (next == EMPTY || next == PILL || next == POWERUP) {
		switch (direction)
		{
			case 1:
				pacman_position.x += IMAGE_WIDTH;
				previous_direction = 1;
				break;
			case 2:
				pacman_position.x -= IMAGE_WIDTH;
				previous_direction = 2;
				break;
			case 3:
				pacman_position.y -=IMAGE_HEIGHT;
				previous_direction = 3;
				break;
			case 4:
				pacman_position.y +=IMAGE_HEIGHT;
				previous_direction = 4;
				break;
		}
	}
	switch (map[n1][m1])
	{

		case 1:
			map[n][m] = 1;
			map[n1][m1] = 80;
				break;
		case 2:
			switch (direction)
			{
				case 1:
					pacman_position.x += IMAGE_WIDTH;
					break;
				case 2:
					pacman_position.x -= IMAGE_WIDTH;
					break;
				case 3:
					pacman_position.y -=IMAGE_HEIGHT;
					break;
				case 4:
					pacman_position.y +=IMAGE_HEIGHT;
			}
			map[n][m] = 1;
			map[n1][m1] = 80;
			break;
		case 3:
			switch (direction)
			{
				case 1:
					pacman_position.x += IMAGE_WIDTH;
					break;
				case 2:
					pacman_position.x -= IMAGE_WIDTH;
					break;
				case 3:
					pacman_position.y -=IMAGE_HEIGHT;
					break;
				case 4:
					pacman_position.y +=IMAGE_HEIGHT;
			}
			map[n][m] = 1;
			map[n1][m1] = 80;
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
	*/
}
