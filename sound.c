#include"sound.h"
/*Function declarations*/
void SDLCALL audio_callback(void *unused, Uint8 *stream, int length)
{
	Uint8 *waveptr;
	/* Set up the pointers */
	waveptr = wave.sound + wave.soundpos;
	/*Send sound to buffer*/
	SDL_memcpy(stream, waveptr, length);
	wave.soundpos += length;
	/*If the sound finished pause audio*/
	if (wave.soundpos >= wave.soundlen - length)
		SDL_PauseAudio(1);
}

void play_sound(const char * file_name)
{
	/* Load the wave file into memory */
	if (SDL_LoadWAV(file_name, &wave.spec, &wave.sound, &wave.soundlen) == NULL)
	{
		fprintf(stderr, "Couldn't load %s: %s\n", file_name, SDL_GetError());
		SDL_Quit();
		exit(2);
	}
	wave.spec.callback = audio_callback;
	/*Play sound*/
	if (SDL_OpenAudio(&wave.spec, NULL) < 0)
	{
		fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
		SDL_FreeWAV(wave.sound);
		SDL_Quit();
		exit(2);
	}
	SDL_PauseAudio(0);
	SDL_Delay(4500);
	SDL_CloseAudio();
}
