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
bool paused = false;
int score = 0;
int level = 1;
float gameSpeed = 0.5f;
float bgX = 0.0f;

Dino dino = {100, 250, 50, 50, 0, false, DINO_IDLE};
Cactus cactus = {SCREEN_WIDTH, 250, 50, 50, nullptr};

bool initGame()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0) return false;
    if(IMG_Init(IMG_INIT_PNG) < 0) return false;
    if(TTF_Init() == -1) return false;

    window = SDL_CreateWindow("Dino Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if( !window || !renderer) return false;

    srand(static_cast<unsigned int>(time(NULL)));

    if(!loadAssets()) return false;

    int index = rand() % cactusVariants.size();
    cactus.texture = cactusVariants[index].texture;
    cactus.y = cactusVariants[index].y;
    cactus.w = cactusVariants[index].w;
    cactus.h = cactusVariants[index].h;

    return true;
}

void updateGame()
{
    if(gameStarted && !gameOver && !paused){
        //gameSpeed = 5.0f + score / 10.0f;
        bgX -= gameSpeed;

        if(bgX <= -SCREEN_WIDTH) bgX = 0.0f;

        updateDino(dino);
        updateCactus(cactus);
        if(checkCollision(dino,cactus)){
            gameOver = true;
            dino.state = DINO_GAMEOVER;
        }

        int newLevel = 1;
        while (score >= 10 * newLevel *(newLevel + 1) / 2){
            newLevel++;
        }
        level = newLevel;

        gameSpeed = 5.0f + (level - 1) * 1.5f;
    }
}

void resetGame()
{
    gameOver = false;
    gameStarted = false;
    paused = false;
    score = 0;
    level = 1;
    gameSpeed = 5.0f;
    bgX = 0.0f;

    dino.x = 100;
    dino.y = 250;
    dino.w = 50;
    dino.h = 50;
    dino.velocityY = 0;
    dino.isJumping = false;
    dino.state = DINO_IDLE;

    int index = rand() % cactusVariants.size();
    cactus.texture = cactusVariants[index].texture;
    cactus.y = cactusVariants[index].y;
    cactus.w = cactusVariants[index].w;
    cactus.h = cactusVariants[index].h;
    cactus.x = SCREEN_WIDTH;
}

void renderGame()
{
    SDL_RenderClear(renderer);
    renderBackground();
    renderDino();
    renderCactus();

    renderText("Score: " + to_string(score), 10, 10);
    renderText("Level: " + to_string(level), 10, 40);

    if(!gameStarted){
        renderText("Press any key to start!", 250, 150);
    }else if(gameOver){
        renderText("Game over!", 300,100);
        renderText("Press any key to restart",250,150);
    }else if(paused){
        renderText("Paused", 350, 150);
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
