//
//  structs.h
//  2D Shooter
//
//  Created by Mai Anh Pham on 5/6/24.
//

#ifndef structs_h
#define structs_h

#include <SDL2/SDL.h>

typedef struct Entity Entity;

typedef struct {
    void (*logic) ();
    void (*draw) ();
} Delegate;

typedef struct {
    SDL_Renderer* renderer;
    SDL_Window* window;
    Delegate delegate;
    int keyboard[MAX_KEYBOARD_KEYS];
} App;

struct Entity {
    float x;
    float y;
    int w;
    int h;
    int dx;
    float dy;
    float health;
    int reload;
    SDL_Texture* texture;
    Entity* next;
};

typedef struct {
    Entity fighterHead, *fighterTail;
    Entity bulletHead, *bulletTail;
} Stage;


#endif /* structs_h */
