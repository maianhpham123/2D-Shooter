//
//  draw.cpp
//  2D Shooter
//
//  Created by Mai Anh Pham on 5/6/24.
//

#include "draw.hpp"

void prepareScene() {
    SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);
    SDL_RenderClear(app.renderer);
}

void presentScene() {
    SDL_RenderPresent(app.renderer);
}

SDL_Texture* loadTexture(const char* filename) {
    SDL_Texture* texture;
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading: %s", filename);
    texture = IMG_LoadTexture(app.renderer, filename);
    return texture;
}

void blit(SDL_Texture* texture, int x, int y) {
    SDL_Rect dest;
    
    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void blitRect(SDL_Texture* texture, SDL_Rect* src, int x, int y) {
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = src->w;
    dest.h = src->h;
    
    SDL_RenderCopy(app.renderer, texture, src, &dest);
}
