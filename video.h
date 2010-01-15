#ifndef VIDEO_H

#define VIDEO_H

#include <SDL.h>
#include <SDL_mixer.h>
#include "engine.h"
/*Surfaces declarations*/
extern SDL_Surface *screen;
extern SDL_Event event;
/*Rectangles declarations*/
extern SDL_Rect ground[4], background_dest;
/*Map declaration*/
extern int map[31][30];

void load_bitmaps(void);
void free_surfaces(void);
SDL_Surface * init_bitmap (const char * file_name);
int init_bitmap_rect(SDL_Rect * name, SDL_Rect * name_destination, int quantity);
void draw(pacman_t *pacman,ghost_t *ghosts);
void draw_lifes(pacman_t *pacman, int lifes_left); 

#endif
