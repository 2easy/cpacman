#ifndef SOUND_H

#define SOUND_H

#include "SDL_audio.h"
#include "SDL_mixer.h"
struct {
	SDL_AudioSpec spec;
	Uint8   *sound;			/* Pointer to wave data */
	Uint32   soundlen;		/* Length of wave data */
	int      soundpos;		/* Current play position */
} wave;

void SDLCALL audio_callback(void *unused, Uint8 *stream, int length);
#endif

