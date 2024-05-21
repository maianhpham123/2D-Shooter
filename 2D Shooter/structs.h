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
typedef struct Texture Texture;

typedef struct {
    void (*logic) ();
    void (*draw) ();
} Delegate;

struct Texture{
    SDL_Texture* texture;
    Texture* next;
    char name[MAX_NAME_LENGTH];
};

typedef struct {
    SDL_Renderer* renderer;
    SDL_Window* window;
    Delegate delegate;
    int keyboard[MAX_KEYBOARD_KEYS];
    Texture textureHead, *textureTail;
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
    int highScore;
} Stage;
/*
    head: act as a head for the linked list, though not an actual but rather
a placeholder to simplify the list management. The next pointer of 'head' points
to the first actual Node of the list
    tail: point to the last bullet in the linked list. It is used to effieciently
append new Node to the end of the list without needing to tranverse the entire list
 => simplify adding, removing and iterating through the linked list
 */

typedef struct {
    int x;
    int y;
    int speed;
} Star;

#endif /* structs_h */
