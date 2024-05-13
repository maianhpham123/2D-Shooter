//
//  background.cpp
//  2D Shooter
//
//  Created by Mai Anh Pham on 5/12/24.
//

#include "background.hpp"

static int backgroundX;
static Star star[MAX_STARS];
static SDL_Texture* background;

void initBackground() {
    background = loadTexture("assets/background.png");
    backgroundX = 0;
}

static void initStarField() {
    int i;
    for (i = 0; i < MAX_STARS; i++) {
        star[i].x = rand() % SCREEN_WIDTH;
        star[i].y = rand() % SCREEN_HEIGHT;
        star[i].speed = 1 + rand() % 8;
    }
}

static void doBackground() {
    if(--backgroundX < -SCREEN_WIDTH) {
        backgroundX = 0;
    }
}

static void doStarField() {
    int i;
    for (i = 0; i < MAX_STARS; i++) {
        star[i].x -= star[i].speed;
        if (star[i].x < 0) {
            star[i].x = SCREEN_WIDTH + star[i].x;
        }
    }
}

static void drawStarField() {
    int i, c;
    for (i = 0; i < MAX_STARS; i++) {
        c = 32 * star[i].speed;
        SDL_SetRenderDrawColor(app.renderer, c, c, c, 255);
        SDL_RenderDrawLine(app.renderer, star[i].x, star[i].y, star[i].x + 3, star[i].y);
    }
}

static void drawBackground() {
    SDL_Rect dest;
    int x;
    
    for (x = backgroundX; x < SCREEN_WIDTH; x+= SCREEN_WIDTH) {
        dest.x = x;
        dest.y = 0;
        dest.w = SCREEN_WIDTH;
        dest.h = SCREEN_HEIGHT;
        
        SDL_RenderCopy(app.renderer, background, NULL, &dest);
    }
}
