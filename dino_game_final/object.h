#ifndef OBJECT_H
#define OBJECT_H

struct Cactus
{
    int x,y,w,h;
};

struct Dino
{
    int x,y,w,h;
    int velocityY;
    bool isJumping = false;
};

void updateDino(Dino& dino);
void updateCactus(Cactus& cactus);
bool checkCollision(const Dino& dino, const Cactus& cactus);

#endif // OBJECT_H
