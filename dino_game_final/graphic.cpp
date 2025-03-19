#include "graphic.h"
#include "game.h"
#include <iostream>

SDL_Texture* dinoTexture = nullptr;
SDL_Texture* cactusTexture = nullptr;
SDL_Texture* backgroundTexture = nullptr;
TTF_Font* font = nullptr;
SDL_Color white = {255, 255, 255, 255};

bool loadAssets()
{
    backgroundTexture = IMG_LoadTexture(renderer, "assets/background.jpg");
    dinoTexture = IMG_LoadTexture(renderer, "assets/dino.jpg");
    cactusTexture = IMG_LoadTexture(renderer, "assets/cactus.png");
    font = TTF_OpenFont("assets/font.ttf", 24);

    if(!backgroundTexture || !dinoTexture || !cactusTexture || !font){
        cout << "Failed to load assets: " << IMG_GetError() << " / " << TTF_GetError() << endl;
        return false;
    }
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
    SDL_RenderCopy(renderer, cactusTexture, NULL, &rect);
}

void renderText(const string& text, int x, int y)
{
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), white);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dest = {x,y, surface -> w, surface -> h};
    SDL_RenderCopy(renderer, texture, NULL, &dest);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void clearGraphics()
{
    SDL_DestroyTexture(dinoTexture);
    SDL_DestroyTexture(cactusTexture);
    SDL_DestroyTexture(backgroundTexture);
    TTF_CloseFont(font);
}
