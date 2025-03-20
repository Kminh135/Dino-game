#include "game.h"
#include "graphic.h"
#include "input.h"
#include "object.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
bool running = true;
bool gameStarted = false;
bool gameOver = false;
int score = 0;
float gameSpeed = 0.5f;


Dino dino = {100, 270, 50, 50, 0, false};
Cactus cactus = {SCREEN_WIDTH, 270, 50, 50, nullptr};

bool initGame()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0) return false;
    if(IMG_Init(IMG_INIT_PNG) < 0) return false;
    if(TTF_Init() == -1) return false;

    window = SDL_CreateWindow("Dino Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if( !window || !renderer) return false;

    if(!loadAssets()) return false;

    int index = rand() % cactusVariants.size();
    cactus.texture = cactusVariants[index].texture;
    cactus.y = cactusVariants[index].y;
    cactus.w = cactusVariants[index].w;
    cactus.h = cactusVariants[index].h;
    int groundY = 270;

    return true;
}

void updateGame()
{
    //if(!gameStarted || gameOver) return;
    if(gameStarted && !gameOver){
        gameSpeed = 5.0f + score / 10.0f;

        updateDino(dino);
        updateCactus(cactus);
        if(checkCollision(dino,cactus)) gameOver = true;
    }
}

void renderGame()
{
    SDL_RenderClear(renderer);
    renderBackground();
    renderDino();
    renderCactus();

    if(!gameStarted){
        renderText("Press any key to start!", 250, 150);
    }else if(gameOver){
        renderText("Game over! Score: " + to_string(score), 250,100);
        renderText("Press any key to restart",250,150);
    }

    SDL_RenderPresent(renderer);
}

void cleanupGame()
{
    clearGraphics();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
}
