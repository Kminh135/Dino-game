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
            if((e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_UP) && !dino.isJumping && !gameOver){
                dino.isJumping = true;
                dino.velocityY = -20;
            }
            if(gameOver && e.key.keysym.sym == SDLK_RETURN){
                gameOver = false;
                gameStarted = false;
                score = 0;
                cactus.x = SCREEN_WIDTH;
                dino.y = 300;
            }
        }
    }
}
