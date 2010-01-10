#include "engine.h"
#include "constants.h"

void move_pacman(pacman_t *pacman,int direction)
{
	/*turning backwards*/
	if (
		direction == UP && pacman->direction == DOWN ||
		direction == DOWN && pacman->direction == UP ||
		direction == RIGHT && pacman->direction == LEFT ||
		direction == LEFT && pacman->direction == RIGHT) {
		pacman->direction = direction;
	}
	
	if (pacman->position.x % 25 == 0 && pacman->position.y % 25 == 0 && direction) {
		int x = pacman->position.x / IMAGE_HEIGHT;
		int y = pacman->position.y / IMAGE_WIDTH;
		switch (direction)
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
		if (map[y][x] == EMPTY || map[y][x] == PILL || map[y][x] == POWERUP || map[y][x] == TELEPORT) {
			pacman->direction = direction;
		}
	}

	if (pacman->position.x % 25 == 0 && pacman->position.y % 25 == 0) {
		int x = pacman->position.x / IMAGE_HEIGHT;
		int y = pacman->position.y / IMAGE_WIDTH;
		switch (pacman->direction)
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
		if (map[y][x] == PILL) {
			map[y][x] = EMPTY;
		} else if (map[y][x] == POWERUP) {
			map[y][x] = EMPTY;
		} else if (map[y][x] == TELEPORT) {
			if (x == 29) {
				pacman->position.x = IMAGE_WIDTH;
			} else {
				pacman->position.x = IMAGE_WIDTH * 28;
			}
			return;
		} else if (map[y][x] == WALL) {
			return;
		}
	}

	switch (pacman->direction)
	{
		case RIGHT:
			pacman->position.x++;
			break;
		case LEFT:
			pacman->position.x--;
			break;
		case UP:
			pacman->position.y--;
			break;
		case DOWN:
			pacman->position.y++;
			break;
		default:
			printf("direction %d\n",direction);
		 	exit(0);
	}
}
