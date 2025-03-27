#ifndef AUDIO_H
#define AUDIO_H

#include <SDL_mixer.h>

bool loadAudio();
void playJumpSound();
void playLevelUpSound();
void playGameOverSound();
void cleanupAudio();

#endif

