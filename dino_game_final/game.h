#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "object.h"
#include <string>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 400;

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern bool running;
extern bool gameStarted;
extern bool gameOver;
extern int score;
extern float gameSpeed;

extern Dino dino;
extern Cactus cactus;

extern float bgX;

bool initGame();
void updateGame();
void resetGame();
void renderGame();
void cleanupGame();


#endif // GAME_H
