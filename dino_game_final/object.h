#ifndef OBJECT_H
#define OBJECT_H

#include <SDL.h>
const int JUMP_FORCE = -17;

enum DinoState
{
    DINO_IDLE, DINO_DUCK, DINO_GAMEOVER
};

struct Dino
{
    int x,y,w,h;
    int velocityY;
    bool isJumping;
    int state;
};

struct Cactus
{
    int x,y,w,h;
    SDL_Texture* texture;
};


void updateDino(Dino& dino);
void updateCactus(Cactus& cactus);
bool checkCollision(const Dino& dino, const Cactus& cactus);

#endif // OBJECT_H
