#include"engine.h"
#include"constants.h"

void move_pacman(int direction)
{
	/*turning backwards*/
	if (
		direction == UP && pacman_direction == DOWN ||
		direction == DOWN && pacman_direction == UP ||
		direction == RIGHT && pacman_direction == LEFT ||
		direction == LEFT && pacman_direction == RIGHT) {
		pacman_direction = direction;
	}
	
	if (pacman_position.x % 25 == 0 && pacman_position.y % 25 == 0 && direction) {
		int x = pacman_position.x / IMAGE_HEIGHT;
		int y = pacman_position.y / IMAGE_WIDTH;
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
			pacman_direction = direction;
		}
	}

	if (pacman_position.x % 25 == 0 && pacman_position.y % 25 == 0) {
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
		if (map[y][x] == PILL) {
			map[y][x] = EMPTY;
		} else if (map[y][x] == POWERUP) {
			map[y][x] = EMPTY;
		} else if (map[y][x] == TELEPORT) {
			if (x == 29) {
				pacman_position.x = IMAGE_WIDTH;
			} else {
				pacman_position.x = IMAGE_WIDTH * 28;
			}
			return;
		} else if (map[y][x] == WALL) {
			return;
		}
	}

	switch (pacman_direction)
	{
		case RIGHT:
			pacman_position.x++;
			break;
		case LEFT:
			pacman_position.x--;
			break;
		case UP:
			pacman_position.y--;
			break;
		case DOWN:
			pacman_position.y++;
			break;
		default:
			printf("direction %d\n",direction);
		 	exit(0);
	}
}
