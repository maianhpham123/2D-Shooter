//
//  init.cpp
//  2D Shooter
//
//  Created by Mai Anh Pham on 5/6/24.
//

#include "init.hpp"

void initSDL() {
    int renderFlags, windowFlags;
    
    renderFlags = SDL_RENDERER_ACCELERATED;
    windowFlags = 0;
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "Could not initialise: " << SDL_GetError() << endl;
        exit(1);
    }
    
    app.window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
    if(!app.window) {
        cerr << "Could not open window: " << SDL_GetError() << endl;
        exit(1);
    }
    
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    
    app.renderer = SDL_CreateRenderer(app.window, -1, renderFlags);
    if (!app.renderer) {
        cerr << "Could not create renderer: " << SDL_GetError() << endl;
        exit(1);
    }
}

void cleanup() {
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
}
