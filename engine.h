#ifndef ENGINE_H

#define ENGINE_H

#include<SDL.h>
/*Surfaces declarations*/
extern SDL_Surface * screen;
extern SDL_Surface *blinky_pic, *inky_pic, *pinky_pic, *clyde_pic, *confused_pic;
extern SDL_Surface *pacman_up_pic, *pacman_down_pic, *pacman_right_pic, *pacman_left_pic;
extern SDL_Surface *ground_pic;
extern SDL_Surface *map_pic;
extern SDL_Event event;
/*Rectangles declarations*/
extern SDL_Rect blinky[4], inky[4], pinky[4], clyde[4], confused[2];
extern SDL_Rect blinky_position, inky_position, pinky_position, clyde_position;
extern SDL_Rect pacman[5], pacman_position;
int pacman_direction;
extern SDL_Rect ground[3], background_dest;
/*Map declaration*/
extern int map[31][30];
extern int n, m, done, state;
int previous_direction = 2;

void move_pacman(int direction);

#endif
