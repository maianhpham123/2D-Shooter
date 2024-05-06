//
//  input.cpp
//  2D Shooter
//
//  Created by Mai Anh Pham on 5/6/24.
//

#include "input.hpp"

void doKeyDown(SDL_KeyboardEvent* event) {
    if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
        app.keyboard[event->keysym.scancode] = 1;
    }
}

void doKeyUp(SDL_KeyboardEvent* event) {
    if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
        app.keyboard[event->keysym.scancode] = 0;
    }
}

void doInput() {
    SDL_Event event;
    
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                exit(0);
                break;
                
            case SDL_KEYDOWN:
                doKeyDown(&event.key);
                break;
                
            case SDL_KEYUP:
                doKeyUp(&event.key);
                break;
                
            default:
                break;
        }
    }
}
