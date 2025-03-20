#include "object.h"
#include "game.h"
#include "graphic.h"
#include <cstdlib>

using namespace std;

const int GRAVITY = 1;


void updateDino(Dino& dino)
{
    if(dino.isJumping){
        dino.y += dino.velocityY;
        dino.velocityY += GRAVITY;
        if(dino.y >= 270)
        {
            dino.y = 270;
            dino.isJumping = false;
        }
    }
}

void updateCactus(Cactus& cactus)
{
    cactus.x -= gameSpeed;
    if(cactus.x < -cactus.w){
        cactus.x = SCREEN_WIDTH;
        score++;

        int index = rand() % cactusVariants.size();
        cactus.texture = cactusVariants[index].texture;
        cactus.y = cactusVariants[index].y;
        cactus.w = cactusVariants[index].w;
        cactus.h = cactusVariants[index].h;
    }
}

bool checkCollision(const Dino& dino, const Cactus& cactus)
{
    return (dino.x < cactus.x + cactus.w && dino.x + dino.w > cactus.x &&
            dino.y < cactus.y + cactus.h && dino.y + dino.h > cactus.y);
}
