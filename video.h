#ifndef VIDEO_H

#define VIDEO_H

#include <SDL.h>
#include "engine.h"
/*Surfaces declarations*/
extern SDL_Surface *screen;
extern SDL_Event event;
/*Rectangles declarations*/
extern SDL_Rect blinky[4], inky[4], pinky[4], clyde[4], confused[2];
extern SDL_Rect blinky_position, inky_position, pinky_position, clyde_position;
extern SDL_Rect ground[4], background_dest;
/*Map declaration*/
extern int map[31][30];

SDL_Surface * init_bitmap (const char * file_name);
int init_bitmap_rect(SDL_Rect * name, SDL_Rect * name_destination, int quantity);
void load_bitmaps(void);
void draw(pacman_t *pacman,ghost_t *ghosts);

#endif
