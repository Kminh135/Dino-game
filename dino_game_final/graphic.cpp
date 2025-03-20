#include "graphic.h"
#include "game.h"
#include "object.h"
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>

SDL_Texture* dinoTexture = nullptr;
//SDL_Texture* cactusTexture = nullptr;
SDL_Texture* backgroundTexture = nullptr;
TTF_Font* font = nullptr;
SDL_Color white = {255, 255, 255, 255};

vector<CactusInfo> cactusVariants;

bool loadAssets()
{
    backgroundTexture = IMG_LoadTexture(renderer, "assets/background.jpg");
    dinoTexture = IMG_LoadTexture(renderer, "assets/dino.jpg");
    //cactusTexture = IMG_LoadTexture(renderer, "assets/cactus.png");

    if(!backgroundTexture || !dinoTexture){
        cout << "Failed to load background or dino texture: " << IMG_GetError() << endl;
        return false;
    }

    font = TTF_OpenFont("assets/font.ttf", 24);
    if(!font){
        cout << "Failed to load font: " << TTF_GetError() << endl;
        return false;
    }

    SDL_Texture* cs1 = IMG_LoadTexture(renderer, "assets/cactus_short1.jpg");
    SDL_Texture* cs2 = IMG_LoadTexture(renderer, "assets/cactus_short2.jpg");
    SDL_Texture* cs3 = IMG_LoadTexture(renderer, "assets/cactus_short3.jpg");
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
    SDL_Rect bgRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &bgRect);
}

void renderDino()
{
    SDL_Rect rect = {dino.x, dino.y, dino.w, dino.h};
    SDL_RenderCopy(renderer, dinoTexture, NULL, &rect);
}

void renderCactus()
{
    SDL_Rect rect = {cactus.x, cactus.y, cactus.w, cactus.h};
    SDL_RenderCopy(renderer, cactus.texture, NULL, &rect);
}

void renderText(const string& text, int x, int y)
{
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), white);
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
    SDL_DestroyTexture(dinoTexture);
    //SDL_DestroyTexture(cactusTexture);
    for (auto &ct : cactusVariants){
        SDL_DestroyTexture(ct.texture);
    }
    cactusVariants.clear();
    TTF_CloseFont(font);
}
