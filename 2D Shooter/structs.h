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
typedef struct Explosion Explosion;
typedef struct Debris Debris;

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
    float dx;
    float dy;
    int health;
    int reload;
    int side;
    SDL_Texture* texture;
    Entity* next;
};

struct Explosion {
    float x;
    float y;
    float dx;
    float dy;
    int r,g,b,a;
    Explosion* next;
};

struct Debris {
    float x;
    float y;
    float dx;
    float dy;
    SDL_Rect rect;
    SDL_Texture* texture;
    int life;
    Debris* next;
};

typedef struct {
    Entity fighterHead, *fighterTail;
    Entity bulletHead, *bulletTail;
    Explosion explosionHead, *explosionTail;
    Debris debrisHead, *debrisTail;
    Entity pointHead, *pointTail;
    int score;
} Stage;

typedef struct {
    int x;
    int y;
    int speed;
} Star;

#endif /* structs_h */
