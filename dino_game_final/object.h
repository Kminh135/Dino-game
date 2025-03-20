#ifndef OBJECT_H
#define OBJECT_H

#include <SDL.h>

struct Dino
{
    int x,y,w,h;
    int velocityY;
    bool isJumping;
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
