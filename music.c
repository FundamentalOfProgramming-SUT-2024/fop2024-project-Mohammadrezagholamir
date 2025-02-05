#include "sound.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

void play_music(const char *filename) {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 16384) < 0) {
        printf("SDL_mixer Initialization failed: %s\n", Mix_GetError());
        return;
    }

    Mix_Music *music = Mix_LoadMUS(filename);
    if (!music) {
        printf("Failed to load music: %s\n", Mix_GetError());
    } else {
        Mix_PlayMusic(music, -1); // -1 یعنی موسیقی تکرار شود
    }
}

void stop_music() {
    Mix_HaltMusic();
    Mix_CloseAudio();
}




