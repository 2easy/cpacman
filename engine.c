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
		if (map[y][x] != WALL && map[y][x] != CAGE) {
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

static void move_ghost(ghost_t *ghost,pacman_t *pacman)
{
	int directions[4] = {ghost->direction, ghost->direction, ghost->direction, ghost->direction};
	int i = 0;
	if (ghost->position.x % 25 == 0 && ghost->position.y % 25 == 0) {
		int x = ghost->position.x / IMAGE_HEIGHT;
		int y = ghost->position.y / IMAGE_WIDTH;
		if (map[y][x+1] != WALL && ghost->direction != LEFT) {
			directions[i++] = RIGHT;
		}
		if (map[y][x-1] != WALL && ghost->direction != RIGHT) {
			directions[i++] = LEFT;
		}
		if (map[y-1][x] != WALL && ghost->direction != DOWN) {
			directions[i++] = UP;
		}
		if (map[y+1][x] != WALL && ghost->direction != UP) {
			directions[i++] = DOWN;
		}
		if (i) ghost->direction = directions[(rand() % i)];
	}

	if (ghost->position.x % 25 == 0 && ghost->position.y % 25 == 0) {
		int x = ghost->position.x / IMAGE_HEIGHT;
		int y = ghost->position.y / IMAGE_WIDTH;
		switch (ghost->direction)
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
				printf("direction %d\n",ghost->direction);
				exit(0);
		}
		if (map[y][x] == TELEPORT) {
			if (x == 29) {
				ghost->position.x = IMAGE_WIDTH;
			} else {
				ghost->position.x = IMAGE_WIDTH * 28;
			}
			return;
		} else if (map[y][x] == WALL) {
			return;
		}
	}

	switch (ghost->direction)
	{
		case RIGHT:
			ghost->position.x++;
			break;
		case LEFT:
			ghost->position.x--;
			break;
		case UP:
			ghost->position.y--;
			break;
		case DOWN:
			ghost->position.y++;
			break;
		default:
			printf("direction %d\n",ghost->direction);
		 	exit(0);
	}
}
void move_ghosts(ghost_t *ghosts,pacman_t *pacman) {
	int i;
	for (i=0;i<4;i++) {
		move_ghost(ghosts+i,pacman);
	}
}
