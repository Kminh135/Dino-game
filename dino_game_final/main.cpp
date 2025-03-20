#include "game.h"
#include "input.h"
#include <ctime>

int main(int argc, char* argv[])
{
    //srand(time(NULL));

    if(!initGame()){
        return -1;
    }

    while(running){
        handleInput();
        updateGame();
        renderGame();
        SDL_Delay(16);
    }

    cleanupGame();
    return 0;
}
