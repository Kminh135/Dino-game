#include "input.h"
#include "game.h"
#include "object.h"
#include <SDL.h>


void handleInput()
{
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT) running = false;
        if(e.type == SDL_KEYDOWN){
            if(!gameStarted){
                gameStarted = true;
            }
            if((e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_UP) &&
               !dino.isJumping && dino.state != DINO_DUCK && !gameOver){
                dino.isJumping = true;
                dino.velocityY = JUMP_FORCE;
            }
            if(!gameOver && e.key.keysym.sym == SDLK_DOWN){
                dino.state = DINO_DUCK;
                dino.w = 100;
                dino.h = 25;
                dino.y = 295;
            }
            if(gameOver && e.type == SDL_KEYDOWN){
                resetGame();
            }
        }
        if(e.type == SDL_KEYUP){
            if(e.key.keysym.sym == SDLK_DOWN && !gameOver){
                dino.state = DINO_IDLE;
                dino.w = 50;
                dino.h = 50;
                dino.y = 270;
            }
        }
    }
}
