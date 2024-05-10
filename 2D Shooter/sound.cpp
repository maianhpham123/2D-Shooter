//
//  sound.cpp
//  2D Shooter
//
//  Created by Mai Anh Pham on 5/10/24.
//

#include "sound.hpp"

static void loadSound();

static Mix_Chunk* sounds[SND_MAX];
static Mix_Music* music;

void initSound() {
    memset(sounds, 0, sizeof(Mix_Chunk*) * SND_MAX);
    music = NULL;
    loadSound();
}

static void loadSound() {
    sounds[SND_PLAYER_FIRE] = Mix_LoadWAV("sound/334227__jradcoolness__laser.ogg");
    sounds[SND_ALIEN_FIRE] = Mix_LoadWAV("sound/196914__dpoggioli__laser-gun.ogg");
    sounds[SND_PLAYER_DIE] = Mix_LoadWAV("sound/245372__quaker540__hq-explosion.ogg");
    sounds[SND_ALIEN_DIE] = Mix_LoadWAV("sound/10 Guage Shotgun-SoundBible.com-74120584.ogg");
}

void loadMusic(const char* filename) {
    if (music != NULL) {
        Mix_HaltMusic();
        Mix_FreeMusic(music);
        music = NULL;
    }
    
    music = Mix_LoadMUS(filename);
}

void playMusic(int loop) {
    Mix_PlayMusic(music, (loop) ? -1 : 0);
}

void playSound(int id, int channel) {
    Mix_PlayChannel(channel, sounds[id], 0);
}
