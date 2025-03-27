#include "audio.h"
#include <iostream>

using namespace std;

Mix_Chunk* jumpSound = nullptr;
Mix_Chunk* levelUpSound = nullptr;
Mix_Chunk* gameOverSound = nullptr;

bool loadAudio() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cout << "SDL_mixer could not initialize! Error: " << Mix_GetError() << endl;
        return false;
    }
    jumpSound = Mix_LoadWAV("assets/jump.wav");
    levelUpSound = Mix_LoadWAV("assets/level_up.wav");
    gameOverSound = Mix_LoadWAV("assets/game_over.wav");
    if (!jumpSound || !levelUpSound || !gameOverSound) {
        cout << "Failed to load audio files! Error: " << Mix_GetError() << endl;
        return false;
    }
  return true;
}

void playJumpSound() {
    Mix_PlayChannel(-1, jumpSound, 0);
}

void playLevelUpSound() {
    Mix_PlayChannel(-1, levelUpSound, 0);
}

void playGameOverSound() {
    Mix_PlayChannel(-1, gameOverSound, 0);
}

void cleanupAudio() {
    Mix_FreeChunk(jumpSound);
    Mix_FreeChunk(levelUpSound);
    Mix_FreeChunk(gameOverSound);
    jumpSound = nullptr;
    levelUpSound = nullptr;
    gameOverSound = nullptr;
    Mix_CloseAudio();
}

