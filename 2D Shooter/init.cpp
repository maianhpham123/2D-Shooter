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
    
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
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
    
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        cerr << "Could not open mixer!" << endl;
        exit(1);
    }
    
    if (TTF_Init() == -1) {
        cerr << "Could not open Fonts!" << TTF_GetError() << endl;
        exit(1);
    }
    
    if (!Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3 | MIX_INIT_WAVPACK)) {
        cerr << "Could not open Music!" << Mix_GetError() << endl;
    }
    
    Mix_AllocateChannels(MAX_SND_CHANNELS);
    
    SDL_ShowCursor(0);
}

void initGame() {
    initBackground();
    initStarField();
    initSound();
    loadMusic("music/Meteor - Death Race (Round 2) (128 kbps).mp3");
    playMusic(1);
}

void cleanup() {
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}
