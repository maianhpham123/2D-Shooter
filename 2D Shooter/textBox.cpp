//
//  textBox.cpp
//  2D Shooter
//
//  Created by Mai Anh Pham on 5/18/24.
//

#include "textBox.hpp"

SDL_Texture* generalTexture;

static int revealTime = FPS * 2;

void drawTextBox() {
    if (--revealTime < 0) return;
    
    SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 100);
    SDL_Rect shadedBox = {0, 500, SCREEN_WIDTH, SCREEN_HEIGHT / 2};
    SDL_RenderFillRect(app.renderer, &shadedBox);
    generalTexture = loadTexture("general.png");
    
    SDL_Rect dest = {2, 400, 470, 400};
    SDL_RenderCopy(app.renderer, generalTexture, NULL, &dest);
    
    drawText("Good luck on your mission!", 40, 500, SCREEN_HEIGHT - 150);
    drawText("And have some fun!", 25, 500, SCREEN_HEIGHT - 100);
}
