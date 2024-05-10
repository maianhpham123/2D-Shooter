//
//  text.cpp
//  2D Shooter
//
//  Created by Mai Anh Pham on 5/10/24.
//

#include "text.hpp"

static TTF_Font* font;
static SDL_Texture* textureText;


void drawText(const char* text, int size, int x, int y) {
    font = TTF_OpenFont("VeniteAdoremus-rgRBA.ttf", size);
    if (font == NULL) {
        cerr << "Could not load font!" << endl;
        exit(1);
    }
    
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, {255,255,255});
    if (textSurface == NULL) cerr << "Fail to create textSurface: " << TTF_GetError() << endl;
    
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(app.renderer, textSurface);
    if (textTexture == NULL) cerr << "Fail to create textTexture: " << TTF_GetError() << endl;
    
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = textSurface->w;
    dest.h = textSurface->h;
    
    SDL_RenderCopy(app.renderer, textTexture, NULL, &dest);
}
