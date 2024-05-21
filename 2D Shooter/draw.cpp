//
//  draw.cpp
//  2D Shooter
//
//  Created by Mai Anh Pham on 5/6/24.
//

#include "draw.hpp"

void prepareScene() {
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 0);
    SDL_RenderClear(app.renderer);
}

void presentScene() {
    SDL_RenderPresent(app.renderer);
}

static SDL_Texture* getTexture(const char* filename) {
    Texture* t;
    for (t = app.textureHead.next; t != NULL; t = t->next) {
        if (strcmp(t->name, filename) == 0) {
            return t->texture;
        }
    }
    return NULL;
}

static void addTextureToCache(const char* filename, SDL_Texture* tex) {
    Texture* texture = (Texture*) malloc(sizeof(Texture));
    memset(texture, 0, sizeof(Texture));

    app.textureTail->next = texture;
    app.textureTail = texture;

    STRNCPY(texture->name, filename, MAX_NAME_LENGTH);
    texture->texture = tex;
}

SDL_Texture* loadTexture(const char* filename) {
    SDL_Texture* texture;
    texture = getTexture(filename);
    if (texture == NULL) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading: %s", filename);
        texture = IMG_LoadTexture(app.renderer, filename);
        addTextureToCache(filename, texture);
    }
    return texture;
}

void blit(SDL_Texture* texture, const int x,const int y) {
    SDL_Rect dest;
    
    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void blitRect(SDL_Texture* texture, SDL_Rect* src, const int x, const int y) {
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = src->w;
    dest.h = src->h;
    
    SDL_RenderCopy(app.renderer, texture, src, &dest);
}
