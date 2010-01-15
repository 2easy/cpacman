#include "engine.h"
#include "constants.h"

void map_init(int map[31][30]) {
	int i, j;
	FILE * map_file;
	/*Open map file*/
	if ((map_file = fopen("map.txt", "r")) == NULL)	{
		fprintf(stderr, "Couldn't open \"map.txt\"\n");
		exit(1);
	}
	/*Convert to the array*/
	for (i = 0; i < 31; i++) {
		for (j = 0; j < 30; j++) {
			char c = getc(map_file);
			switch (c) {
				case ' ':
					map[i][j] = EMPTY;
					break;
				case '.':
					map[i][j] = PILL;
					break;
				case 'P':
					map[i][j] = POWERUP;
					break;
				case '#':
					map[i][j] = WALL;
					break;
				case 'T':
					map[i][j] = TELEPORT;
					break;
				case 'C':
					map[i][j] = CAGE;
					break;
				default:
					printf("Unknown char: %c\n",c);
					exit(0);
			}
		}
		getc(map_file);
	}	
	fclose(map_file);
}

void characters_init(pacman_t *pacman, ghost_t *ghosts, int *direction,  SDL_Rect *background_dest) {
	int i;
	/*Pacman*/
	pacman->animation_state = 0 * PACMAN_ANIMATION_SPEED;
	pacman->direction = LEFT;
	pacman->speed = PACMAN_SPEED;
	pacman->slow = 0;
	*direction = NONE;
	/*Ghosts*/
	for (i=0;i<4;i++) {
		ghosts[i].animation_state = 0;
		ghosts[i].direction = LEFT;
		ghosts[i].image = i;
		ghosts[i].speed = GHOST_SPEED;
		ghosts[i].weakness_state = NORMAL;
		ghosts[i].time_to_recover = 0;
	}
	set_all_start_positions(pacman, ghosts, background_dest);
}

void set_start_position(SDL_Rect *name_destination, int n, int m) {
	name_destination->x = m * IMAGE_WIDTH;
	name_destination->y = n * IMAGE_HEIGHT;
}

void set_all_start_positions(pacman_t *pacman, ghost_t *ghosts, SDL_Rect *background_dest) {
	set_start_position(&pacman->position, 23, 15);
	set_start_position(&ghosts[BLINKY].position, 11, 15);
	set_start_position(&ghosts[INKY].position, 14, 14);
	set_start_position(&ghosts[PINKY].position, 14, 15);
	set_start_position(&ghosts[CLYDE].position, 14, 16);
	set_start_position(background_dest, 0, 1);
}

void bring_ghosts_morale_back(ghost_t *ghosts) {
	int i;

	for (i = 0; i < 4; i++) {
		if (ghosts[i].weakness_state != DEAD) {
			ghosts[i].time_to_recover--;
			if (ghosts[i].weakness_state == TELEPORTED && ghosts[i].time_to_recover == 0) {
				ghosts[i].weakness_state = NORMAL;
			}
			if (ghosts[i].time_to_recover == (TIME_TO_RECOVER / 3) && ghosts[i].weakness_state == WEAK) {
					ghosts[i].weakness_state = FLASHING;
				} else if (ghosts[i].time_to_recover <= 0 && ghosts[i].weakness_state == FLASHING) {
					ghosts[i].animation_state = 0;
					ghosts[i].weakness_state = NORMAL;
					ghosts[i].time_to_recover = 0;
			}	
		}
		if (ghosts[i].weakness_state == NORMAL || ghosts[i].weakness_state == DEAD) {
			ghosts[i].speed = GHOST_SPEED;
		}
		if (ghosts[i].position.x >= 14 * IMAGE_WIDTH && ghosts[i].position.x <= 15 * IMAGE_WIDTH
		&& ghosts[i].position.y <= 14 * IMAGE_HEIGHT && ghosts[i].position.y >= 13 * IMAGE_HEIGHT) {
			ghosts[i].weakness_state = NORMAL;
		}
	}
}

void move_pacman(pacman_t *pacman, int direction, int *score) {
	/*Turning backwards*/
	if (	direction == UP && pacman->direction == DOWN ||
		direction == DOWN && pacman->direction == UP ||
		direction == RIGHT && pacman->direction == LEFT ||
		direction == LEFT && pacman->direction == RIGHT  ) {
		pacman->direction = direction;
	}
	/*Check if pacman is can change direction*/
	if (pacman->position.x % IMAGE_WIDTH == 0 && pacman->position.y % IMAGE_HEIGHT == 0) {
		int x = pacman->position.x / IMAGE_HEIGHT;
		int y = pacman->position.y / IMAGE_WIDTH;
		/*Check if user pressed the DIRECTION key*/
		if (direction) {
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
				printf("Direction %d\n",direction);
		 		exit(0);

			}
			if (map[y][x] != WALL && map[y][x] != CAGE) {
				pacman->direction = direction;
			}
		} 
		/*Check movement with map*/
		x = pacman->position.x / IMAGE_HEIGHT;
		y = pacman->position.y / IMAGE_WIDTH;
		if (map[y][x] == PILL) {
			*score += 10;
			map[y][x] = EMPTY;
			pacman->slow = 5;
		} else if (map[y][x] == POWERUP) {
			map[y][x] = EMPTY;
			have_powerup = 1;
		}
		switch (pacman->direction) {
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
				printf("Direction %d\n",pacman->direction);
		 		exit(0);
		}
		if (map[y][x] == TELEPORT) {
			if (x == 29) {
				pacman->position.x = IMAGE_WIDTH * 1;
			} else {
				pacman->position.x = IMAGE_WIDTH * 28;
			}
			return;
		} else if (map[y][x] == WALL) {
				return;
		}
	}
	/*Move sprite*/	
	switch (pacman->direction) {
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
			printf("Direction: %d\n",pacman->direction);
		 	exit(0);
	}
}

int allot_direction(ghost_t *ghost) {
	int directions[4] = {ghost->direction, ghost->direction, ghost->direction, ghost->direction};	
	int x = ghost->position.x / IMAGE_WIDTH;
	int y = ghost->position.y / IMAGE_HEIGHT;
	int i = 0;

	if (map[y][x+1] != WALL && ghost->direction != LEFT) {
		directions[i++] = RIGHT;
	}
	if (map[y][x-1] != WALL && ghost->direction != RIGHT) {
		directions[i++] = LEFT;
	}
	if (map[y-1][x] != WALL && ghost->direction != DOWN) {
		directions[i++] = UP;
	}
	if (map[y+1][x] != WALL && map[y+1][x] != CAGE && ghost->direction != UP) {
		directions[i++] = DOWN;
	}
	return directions[(rand() % i)];
}

int get_direction_towards(ghost_t *ghost, int n, int m) {
	int directions[4] = {ghost->direction, ghost->direction, ghost->direction, ghost->direction};	
	int x = ghost->position.x / IMAGE_WIDTH;
	int y = ghost->position.y / IMAGE_HEIGHT;
	if (ghost->position.x < m * IMAGE_WIDTH && map[y][x+1] != WALL && ghost->direction != LEFT) {
		return RIGHT;
	} else if (ghost->position.x > m * IMAGE_WIDTH && map[y][x-1] != WALL && ghost->direction != RIGHT) {
		return LEFT;
	} else if (ghost->position.y < n * IMAGE_HEIGHT && map[y+1][x] != WALL && ghost->direction != UP) {
		return DOWN;
	} else if (ghost->position.y > n * IMAGE_HEIGHT && map[y-1][x] != WALL && ghost->direction != DOWN) {
		return UP;
	}
	return allot_direction(ghost);
}

void move_ghost(ghost_t *ghost, int ghost_name, pacman_t *pacman) {
	/*Check if I can change direction*/
	if (ghost->position.x % IMAGE_WIDTH == 0 && ghost->position.y % IMAGE_HEIGHT == 0) {
		/*Get my position*/
		int x = ghost->position.x / IMAGE_WIDTH;
		int y = ghost->position.y / IMAGE_HEIGHT;
		/*If I'm in cage, get out of it*/
		if (ghost->weakness_state != DEAD && map[y][x] == CAGE) {
			if (map[y-1][x] != WALL) {
				ghost->direction = UP;
			} else if (map[y][x-1] != WALL) {
				ghost->direction = LEFT;
			} else {
				ghost->direction = RIGHT;
			}
		} else if (ghost->weakness_state == DEAD) {
			/*Go to cage*/
			ghost->direction = get_direction_towards(ghost, 14, 14);
		} else if (ghost->weakness_state == WEAK || ghost->weakness_state == FLASHING) {
			/*Run away from pacman*/
			ghost->direction = allot_direction(ghost);
		} else {
			if (ghost_name != BLINKY) {
				ghost->direction = allot_direction(ghost);
			} else {
				/*Blinky's tactic*/
				int tactic = rand() % 5;
				if (tactic) {
					int pacman_x = pacman->position.x / IMAGE_WIDTH;
					int pacman_y = pacman->position.y / IMAGE_HEIGHT;
					ghost->direction = get_direction_towards(ghost, pacman_y, pacman_x);
				} else {
					ghost->direction = allot_direction(ghost);
				}
			}
		}
		/*Move within chosen direction*/
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
				printf("Direction %d\n", ghost->direction);
				exit(0);
		}
		if (map[y][x] == TELEPORT) {
			if (ghost->weakness_state == NORMAL) {
				ghost->time_to_recover = AFTER_TELEPORT;
				ghost->weakness_state = TELEPORTED;
			}
			if (x == 29) {
				ghost->position.x = IMAGE_WIDTH *1;
			} else {
				ghost->position.x = IMAGE_WIDTH * 28;
			}
			return;
		} else if (map[y][x] == WALL) {
			return;
		}
	}
	/*Move sprite*/
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
			printf("Direction %d\n", ghost->direction);
			exit(0);
	}
}

int ghosts_collision(pacman_t *pacman, ghost_t *ghosts) {
	int i;
	/*Check for collision*/
	for (i=0;i<4;i++) {
		if (abs(ghosts[i].position.x-pacman->position.x) < TOLERANCE && abs(ghosts[i].position.y-pacman->position.y) < TOLERANCE) {
			return i;
		}
	}
	return NOT_CAUGHT;
}

int pills_left(void) {
	int i, j, pills = 0;
	/*Check if there is anyting to eat for pacman*/
	for (i = 1; i < 30; i++) {
		for (j = 1; j < 28; j++) {
			if (map[j][i] == PILL) {
				pills++;
			}
		}
	}
	return pills;	
}

unsigned int high_score (unsigned int score) {
	FILE * hisc;
	unsigned int hiscore;
	/*Open high score file*/
	if ((hisc = fopen("hiscore.txt", "r+b")) == NULL) {
		fprintf(stderr, "Nie mozna otworzyc pliku\"high_score.txt\"");
		exit(1);
	}
	/*Read current hiscore and check with player score*/
	fread(&hiscore, sizeof (unsigned int), 1, hisc);
	if (score > hiscore) {
		hiscore = score;
		fclose(hisc);
		hisc = fopen("hiscore.txt", "w");
		fwrite(&score, sizeof (unsigned int), 1, hisc);
	}
	fclose(hisc);
	return hiscore;
}
