//
//  stage.cpp
//  2D Shooter
//
//  Created by Mai Anh Pham on 5/6/24.
//

#include "stage.hpp"

static void logic();
static void draw();
static void initPlayer();
static void doPlayer();
static void doBullet();
static void fireBullet();
static void drawPlayer();
static void drawBullet();

static Entity* player;
static SDL_Texture* bulletTexture;

void initStage() {
    app.delegate.logic = logic;
    app.delegate.draw = draw;
    
    memset(&stage, 0, sizeof(Stage));
    stage.fighterTail = &stage.fighterHead;
    stage.bulletTail = &stage.bulletHead;
    
    initPlayer();
    
    bulletTexture = loadTexture("assets/playerBullet.png");
}

static void initPlayer() {
    player = (Entity*) malloc(sizeof(Entity));
    memset(player, 0, sizeof(Entity));
    stage.fighterTail->next = player;
    stage.fighterTail = player;
    
    player->x = 100;
    player->y = 100;
    player->texture = loadTexture("assets/player.png");
    SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

static void logic() {
    doPlayer();
    doBullet();
}

static void doPlayer() {
    player->dx = player->dy = 0;
    
    if (player->reload > 0) player->reload--;
    
    if (app.keyboard[SDL_SCANCODE_UP]) player->dy = -PLAYER_SPEED;
    if (app.keyboard[SDL_SCANCODE_DOWN]) player->dy = +PLAYER_SPEED;
    if (app.keyboard[SDL_SCANCODE_LEFT]) player->dx = -PLAYER_SPEED;
    if (app.keyboard[SDL_SCANCODE_RIGHT]) player->dx = +PLAYER_SPEED;
    if (app.keyboard[SDL_SCANCODE_LSHIFT] && player->reload == 0) fireBullet();
    
    player->x += player->dx;
    player->y += player->dy;
}

static void fireBullet() {
    Entity* bullet;
    bullet = (Entity*) malloc(sizeof(Entity));
    memset(bullet, 0, sizeof(Entity));
    stage.bulletTail->next = bullet;
    stage.bulletTail = bullet;
    
    bullet->x = player->x;
    bullet->y = player->y;
    bullet->dx = PLAYER_BULLET_SPEED;
    bullet->health = 1;
    bullet->texture = bulletTexture;
    SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);
    
    bullet->y += (player->h / 2) - (bullet->h / 2);
    player->reload = 8;
}

static void doBullet() {
    Entity *b, *prev;
    prev = &stage.bulletHead;
    
    for (b = stage.bulletHead.next; b != NULL; b = b->next) {
        b->x += b->dx;
        b->y += b->dy;
        
        if (b->x > SCREEN_WIDTH) {
            if (b == stage.bulletTail) {
                stage.bulletTail = prev;
            }
            
            prev->next = b->next;
            free(b);
            b = prev;
        }
    }
    
    prev = b;
}

static void draw() {
    drawPlayer();
    drawBullet();
}

static void drawPlayer() {
    blit(player->texture, player->x, player->y);
}

static void drawBullet() {
    Entity* b;
    for (b = stage.bulletHead.next; b != NULL; b = b->next) {
        blit(b->texture, b->x, b->y);
    }
}

static void capFrameRate(long* then, float* remainder) {
    long wait, frameTime;
    wait = 16 + *remainder;
    *remainder -= (int) *remainder;
    frameTime = SDL_GetTicks() - *then;
    wait -= frameTime;
    
    if (wait < 1) wait = 1;
    SDL_Delay(wait);
    
    *remainder += 0.667;
    *then = SDL_GetTicks();
}
