//
//  title.cpp
//  2D Shooter
//
//  Created by Mai Anh Pham on 5/14/24.
//

#include "title.hpp"

static void titleLogic();
static void titleDraw();
static void drawLogo();

static SDL_Texture* shooterTexture;

static int reveal = 0;

void initTitle() {
    app.delegate.logic = titleLogic;
    app.delegate.draw = titleDraw;
    
    memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);
    
    shooterTexture = loadTexture("assets/shooter.png");
}

static void titleLogic() {
    doBackground();
    doStarField();
    
    if (reveal < SCREEN_HEIGHT) {
        reveal++;
    }
    
    if (app.keyboard[SDL_SCANCODE_LSHIFT]) {
        if (shooterTexture) SDL_DestroyTexture(shooterTexture);
        initStage();
    }
}

static void titleDraw() {
    drawBackground();
    drawStarField();
    drawLogo();
    drawText("PRESS SHIFT TO FIRE!", 25,470,600);
}

static void drawLogo() {
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    
    SDL_QueryTexture(shooterTexture, NULL, NULL, &rect.w, &rect.h);
    rect.h = min(reveal, rect.h);
    blitRect(shooterTexture, &rect, (SCREEN_WIDTH / 2) - (rect.w / 2), (SCREEN_HEIGHT / 2) - (rect.h / 2));
}
