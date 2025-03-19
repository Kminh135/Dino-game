#include "object.h"
#include "game.h"

using namespace std;

const int GRAVITY = 1;
const int JUMP_FORCE = -20;

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
    cactus.x -= 5;
    if(cactus.x < -cactus.w){
        cactus.x = 800;
        score++;
    }
}

bool checkCollision(const Dino& dino, const Cactus& cactus)
{
    return (dino.x < cactus.x + cactus.w && dino.x + dino.w > cactus.x &&
            dino.y < cactus.y + cactus.h && dino.y + dino.h > cactus.y);
}
