#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "object.h"

using namespace std;

bool loadAssets();
void renderBackground();
void renderDino();
void renderCactus();
void renderText(const string& text, int x,int y);
void clearGraphics();


#endif // GRAPHIC_H

