#include "graphic.h"
#include "game.h"
#include "object.h"
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>


//SDL_Texture* cactusTexture = nullptr;
SDL_Texture* backgroundTexture = nullptr;

SDL_Texture* dinoTextures[6] = {nullptr};

TTF_Font* font = nullptr;
SDL_Color white = {255, 255, 255, 255};
SDL_Color black = {0, 0, 0, 255};

vector<CactusInfo> cactusVariants;

bool loadAssets()
{
    backgroundTexture = IMG_LoadTexture(renderer, "assets/background.png");
    //dinoTexture = IMG_LoadTexture(renderer, "assets/dino.png");
    //cactusTexture = IMG_LoadTexture(renderer, "assets/cactus.png");

    if(!backgroundTexture){
        cout << "Failed to load background texture: " << IMG_GetError() << endl;
        return false;
    }

    dinoTextures[0] = IMG_LoadTexture(renderer, "assets/dino1.png"); // đứng im hoặc nhảy
    dinoTextures[1] = IMG_LoadTexture(renderer, "assets/dino2.png"); // bước chân trái
    dinoTextures[2] = IMG_LoadTexture(renderer, "assets/dino3.png"); // bước chân phải
    dinoTextures[3] = IMG_LoadTexture(renderer, "assets/dino4.png"); // cúi bước chân trái
    dinoTextures[4] = IMG_LoadTexture(renderer, "assets/dino5.png"); // cúi bước chân phải
    dinoTextures[5] = IMG_LoadTexture(renderer, "assets/dino6.png"); // gameover

    for(int i = 0; i < 6; i++){
        if(!dinoTextures[i]){
            cout << "Failed to load dino texture " << i + 1 << ": " << IMG_GetError() <<endl;
            return false;
        }
    }

    font = TTF_OpenFont("assets/font.ttf", 24);
    if(!font){
        cout << "Failed to load font: " << TTF_GetError() << endl;
        return false;
    }

    SDL_Texture* cs1 = IMG_LoadTexture(renderer, "assets/cactus_short1.png");
    SDL_Texture* cs2 = IMG_LoadTexture(renderer, "assets/cactus_short2.png");
    SDL_Texture* cs3 = IMG_LoadTexture(renderer, "assets/cactus_short3.png");
    SDL_Texture* ct1 = IMG_LoadTexture(renderer, "assets/cactus_tall1.png");
    SDL_Texture* ct2 = IMG_LoadTexture(renderer, "assets/cactus_tall2.png");
    SDL_Texture* ct3 = IMG_LoadTexture(renderer, "assets/cactus_tall3.png");

    if(!cs1 || !cs2 || !cs3 || !ct1 || !ct2 || !ct3){
        cout << "Failed to load one of the cactus textures: " << IMG_GetError() <<endl;
        return false;
    }

    cactusVariants.push_back({ct1, 270, 25, 50});
    cactusVariants.push_back({ct2, 270, 50, 50});
    cactusVariants.push_back({ct3, 270, 75, 50});

    cactusVariants.push_back({cs1, 295, 25, 25});
    cactusVariants.push_back({cs2, 295, 50, 25});
    cactusVariants.push_back({cs3, 295, 75, 25});

    return true;
}

void renderBackground()
{
    SDL_Rect bgRect1 = { (int)bgX, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Rect bgRect2 = { (int)bgX + SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    //SDL_Rect bgRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &bgRect1);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &bgRect2);
}

void renderDino()
{
    SDL_Texture* currentTexture = nullptr;

    if(gameOver){
        currentTexture = dinoTextures[5];
    }
    else if(dino.isJumping){
        currentTexture = dinoTextures[0];
    }
    else if(dino.state == DINO_DUCK){
        if((SDL_GetTicks() / 200) % 2 == 0)
            currentTexture = dinoTextures[3];
        else
            currentTexture = dinoTextures[4];
    }
    else{
        if(gameStarted){
            if((SDL_GetTicks() / 200) % 2 == 0)
                currentTexture = dinoTextures[1];
            else
                currentTexture = dinoTextures[2];
        }
        else{
            currentTexture = dinoTextures[0];
        }
    }

    SDL_Rect rect = {dino.x, dino.y, dino.w, dino.h};
    SDL_RenderCopy(renderer, currentTexture, NULL, &rect);
}

void renderCactus()
{
    SDL_Rect rect = {cactus.x, cactus.y, cactus.w, cactus.h};
    SDL_RenderCopy(renderer, cactus.texture, NULL, &rect);
}

void renderText(const string& text, int x, int y)
{
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), black);
    if(!surface){
        cout << "Failed to create text surface: " << TTF_GetError() << endl;
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(!texture){
        cout << "Failed to create text texture: " << SDL_GetError() << endl;
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect dest = {x,y, surface -> w, surface -> h};
    SDL_RenderCopy(renderer, texture, NULL, &dest);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void clearGraphics()
{
    SDL_DestroyTexture(backgroundTexture);
    for(int i = 0; i < 6; i++){
        SDL_DestroyTexture(dinoTextures[i]);
    }
    //SDL_DestroyTexture(dinoTexture);
    //SDL_DestroyTexture(cactusTexture);
    for (auto &ct : cactusVariants){
        SDL_DestroyTexture(ct.texture);
    }
    cactusVariants.clear();
    TTF_CloseFont(font);
}
