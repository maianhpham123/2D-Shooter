//
//  title.hpp
//  2D Shooter
//
//  Created by Mai Anh Pham on 5/14/24.
//

#ifndef title_hpp
#define title_hpp

#include "commons.h"

SDL_Texture* loadTexture(const char* filename);
static void doBackground();
static void doStarField();
static void initStage();
static void drawBackground();
static void drawStarField();
void blitRect(SDL_Texture* texture, SDL_Rect* src, int x, int y);
void drawText(const char* text, int size, int x, int y);
extern App app;

#endif /* title_hpp */
