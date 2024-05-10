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
static void drawBackground();
static void drawStarField();
static void drawFighter();
static void drawBullet();
static void drawExplosion();
static void drawDebris();
static void doFighter();
static void spawnEnemy();
static int bulletHitFighter(Entity* b);
static void resetStage();
static void clipPlayer();
static void doEnemy();
static void fireAlienBullet(Entity* e);
static void initStarField();
static void doBackground();
static void doStarField();
static void doExplosion();
static void doDebris();
static void addExplosion(int x, int y, int number);
static void addDebris(Entity* e);
static void drawHud();

static Entity* player;
static SDL_Texture* bulletTexture;
static SDL_Texture* enemyTexture;
static SDL_Texture* playerTexture;
static SDL_Texture* alienBulletTexture;
static SDL_Texture* background;
static SDL_Texture* explosionTexture;

static int enemySpawnTimer;
static int stageResetTimer;

static int backgroundX = 0;
static Star star[MAX_STARS];

void initStage() {
    app.delegate.logic = logic;
    app.delegate.draw = draw;
    
    memset(&stage, 0, sizeof(Stage));
    stage.fighterTail = &stage.fighterHead;
    stage.bulletTail = &stage.bulletHead;
    stage.explosionTail = &stage.explosionHead;
    stage.debrisTail = &stage.debrisHead;
    
    bulletTexture = loadTexture("assets/playerBullet.png");
    enemyTexture = loadTexture("assets/enemy.png");
    alienBulletTexture = loadTexture("assets/alienBullet.png");
    playerTexture = loadTexture("assets/player.png");
    background = loadTexture("assets/background.png");
    explosionTexture = loadTexture("assets/explosion.png");
    
    memset(&app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);
    
    resetStage();
    
    initPlayer();
    initStarField();
    
    enemySpawnTimer = 0;
    stageResetTimer = FPS * 3;
}

static void initPlayer() {
    player = (Entity*) malloc(sizeof(Entity));
    memset(player, 0, sizeof(Entity));
    stage.fighterTail->next = player;
    stage.fighterTail = player;
    
    player->health = 1;
    player->x = 100;
    player->y = 100;
    player->texture = playerTexture;
    player->side = SIDE_PLAYER;
    
    SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

static void initStarField() {
    int i;
    for (i = 0; i < MAX_STARS; i++) {
        star[i].x = rand() % SCREEN_WIDTH;
        star[i].y = rand() % SCREEN_HEIGHT;
        star[i].speed = 1 + rand() % 8;
    }
}

static void resetStage() {
    Entity* e;
    Explosion* ex;
    Debris* d;
    
    while(stage.explosionHead.next) {
        ex = stage.explosionHead.next;
        stage.explosionHead.next = ex->next;
        free(ex);
    }
    
    while(stage.debrisHead.next) {
        d = stage.debrisHead.next;
        stage.debrisHead.next = d->next;
        free(d);
    }
    
    while(stage.fighterHead.next) {
        e = stage.fighterHead.next;
        stage.fighterHead.next = e->next;
        free(e);
    }
    
    while(stage.bulletHead.next) {
        e = stage.bulletHead.next;
        stage.bulletHead.next = e->next;
        free(e);
    }
    
    stage.fighterTail = &stage.fighterHead;
    stage.bulletTail = &stage.bulletHead;
    stage.explosionTail = &stage.explosionHead;
    stage.debrisTail = &stage.debrisHead;
    
    stage.score = 0;
}

static void logic() {
    doBackground();
    doStarField();
    doPlayer();
    doEnemy();
    doFighter();
    doBullet();
    spawnEnemy();
    clipPlayer();
    doExplosion();
    doDebris();
    
    if (player == NULL && --stageResetTimer <= 0) {
        resetStage();
    }
}

static void doBackground() {
    if(--backgroundX < -SCREEN_WIDTH) {
        backgroundX = 0;
    }
}

static void doStarField() {
    int i;
    for (i = 0; i < MAX_STARS; i++) {
        star[i].x -= star[i].speed;
        if (star[i].x < 0) {
            star[i].x = SCREEN_WIDTH + star[i].x;
        }
    }
}

static void doPlayer() {
    if (player != NULL) {
        player->dx = player->dy = 0;
        
        if (player->reload > 0) player->reload--;
        
        if (app.keyboard[SDL_SCANCODE_UP]) player->dy = -PLAYER_SPEED;
        if (app.keyboard[SDL_SCANCODE_DOWN]) player->dy = PLAYER_SPEED;
        if (app.keyboard[SDL_SCANCODE_LEFT]) player->dx = -PLAYER_SPEED;
        if (app.keyboard[SDL_SCANCODE_RIGHT]) player->dx = PLAYER_SPEED;
        if (app.keyboard[SDL_SCANCODE_LSHIFT] && player->reload == 0) {
            playSound(SND_PLAYER_FIRE, CH_PLAYER);
            fireBullet();
        }
    }
}

static void clipPlayer() {
    if (player != NULL) {
        if (player->x < 0) player->x = 0;
        if (player->y < 0) player->y = 0;
        if (player->x > SCREEN_WIDTH / 2) player->x = SCREEN_WIDTH / 2;
        if (player->y > SCREEN_HEIGHT - player->h) player->y = SCREEN_HEIGHT - player->h;
    }
}

static void doEnemy() {
    Entity* e;
    for (e = stage.fighterHead.next; e != NULL; e = e->next) {
        if (e != player && player != NULL && --e->reload <= 0) {
            fireAlienBullet(e);
            playSound(SND_ALIEN_FIRE, CH_ALIEN_FIRE);
        }
    }
}

static void fireAlienBullet(Entity* e) {
    Entity* bullet;
    
    bullet = (Entity*) malloc(sizeof(Entity));
    memset(bullet, 0, sizeof(Entity));
    stage.bulletTail->next = bullet;
    stage.bulletTail = bullet;
    
    bullet->x = e->x;
    bullet->y = e->y;
    bullet->health = 1;
    bullet->texture = alienBulletTexture;
    bullet->side = e->side;
    SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);
    
    bullet->x += (e->w / 2) - (bullet->w / 2);
    bullet->y += (e->h / 2) - (bullet->h / 2);
    
    calcSlope((int) player->x + (player->w / 2),(int) player->y + (player->h / 2), (int) e->x,(int) e->y, &bullet->dx, &bullet->dy);
    
    bullet->dx *= ALIEN_BULLET_SPEED;
    bullet->dy *= ALIEN_BULLET_SPEED;
    bullet->side = SIDE_ALIEN;
    e->reload = (rand() % FPS * 2);
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
    bullet->side = player->side;
    
    SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);
    
    bullet->y += (player->h / 2) - (bullet->h / 2);
    
    bullet->side = SIDE_PLAYER;
    player->reload = 8;
}

static void doBullet() {
    Entity *b, *prev;
    prev = &stage.bulletHead;
    
    for (b = stage.bulletHead.next; b != NULL; b = b->next) {
        b->x += b->dx;
        b->y += b->dy;
        
        if (bulletHitFighter(b) || b->x < -b->w || b->y < -b->h || b->x > SCREEN_WIDTH || b->y > SCREEN_HEIGHT) {
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

static int bulletHitFighter(Entity* b) {
    Entity* e;
    for (e = stage.fighterHead.next; e != NULL; e = e->next) {
        if  (e->side != b->side && collision(b->x, b->y, b->w, b->h, e->x, e->y, e->w, e->h)) {
            b->health = 0;
            e->health = 0;
            
            if (e == player) playSound(SND_PLAYER_DIE, CH_PLAYER);
            else {
                playSound(SND_ALIEN_DIE, CH_ANY);
                stage.score++;
            }
            
            addExplosion(e->x, e->y, 32);
            addDebris(e);
            
            return 1;
        }
    }
    return 0;
}

static void doFighter() {
    Entity *e, *prev;
    prev = &stage.fighterHead;
    
    for (e = stage.fighterHead.next; e != NULL; e = e->next) {
        e->x += e->dx;
        e->y += e->dy;
        
        if (e != player && e->x < -e->w) {
            e->health = 0;
        }
        
        if (e->health == 0) {
            if (e == player) player = NULL;
            if (e == stage.fighterTail) {
                stage.fighterTail = prev;
            }
            prev->next = e->next;
            free(e);
            e = prev;
        }
        
        prev = e;
    }
}

static void spawnEnemy() {
    Entity* enemy;
    if (--enemySpawnTimer <= 0) {
        enemy = (Entity*) malloc(sizeof(Entity));
        memset(enemy, 0, sizeof(Entity));
        stage.fighterTail->next = enemy;
        stage.fighterTail = enemy;
        
        enemy->x = SCREEN_WIDTH;
        enemy->y = rand() % SCREEN_HEIGHT;
        enemy->side = SIDE_ALIEN;
        
        enemy->texture = enemyTexture;
        SDL_QueryTexture(enemyTexture, NULL, NULL, &enemy->w, &enemy->h);
        enemy->dx = -(2 + (rand() % 4));
        
        enemy->side = SIDE_ALIEN;
        enemy->health = 1;
        
        enemy->reload = FPS * (1 + (rand() % 3));
        enemySpawnTimer = 30 + (rand() % FPS);
    }
}

static void doExplosion() {
    Explosion *e, *prev;
    prev = &stage.explosionHead;
    
    for (e = stage.explosionHead.next; e != NULL; e = e->next) {
        e->x += e->dx;
        e->y += e->dy;
        
        if (--e->a <= 0) {
            if (e == stage.explosionTail) stage.explosionTail = prev;
            
            prev->next = e->next;
            free(e);
            e = prev;
        }
        prev = e;
    }
}

static void doDebris() {
    Debris *d, *prev;
    prev = &stage.debrisHead;
    
    for (d = stage.debrisHead.next; d != NULL; d = d->next) {
        d->x += d->dx;
        d->y += d->dy;
        
        d->dy += 0.5;
        
        if (--d->life <= 0) {
            if (d == stage.debrisTail) stage.debrisTail = prev;
            prev->next = d->next;
            free(d);
            d = prev;
        }
        
        prev = d;
    }
}

static void addExplosion(int x, int y, int num) {
    Explosion* e;
    int i;
    
    for (i = 0; i < num; i++) {
        e = (Explosion*) malloc(sizeof(Explosion));
        memset(e, 0, sizeof(Explosion));
        stage.explosionTail->next = e;
        stage.explosionTail = e;
        
        e->x = x + (rand() % 32) - (rand() % 32);
        e->y = y + (rand() % 32) - (rand() % 32);
        e->dx = (rand() % 10) - (rand() % 10);
        e->dy = (rand() % 10) - (rand() % 10);
        
        e->dx /= 10;
        e->dy /= 10;
        
        switch (rand() % 4) {
            case 0:
                e->r = 255;
                break;
                
            case 1:
                e->r = 255;
                e->g = 128;
                break;
                
            case 2:
                e->r = 255;
                e->g = 255;
                break;
                
            default:
                e->r = 255;
                e->g = 255;
                e->b = 255;
                break;
        }
        e->a = rand() % FPS * 3;
    }
}

static void addDebris(Entity* e) {
    Debris *d;
    int x, y, w, h;
    w = e->w / 2;
    h = e->h / 2;
    
    for (y = 0; y <= h; y+= h) {
        for (x = 0; x <= w; x += w) {
            d = (Debris*) malloc(sizeof(Debris));
            memset(d, 0, sizeof(Debris));
            stage.debrisTail->next = d;
            stage.debrisTail = d;
            
            d->x = e->x + e->w/2;
            d->y = e->y + e->h/2;
            d->dx = (rand() % 5) - (rand() % 5);
            d->dy = -(5 + rand() % 12);
            d->life = FPS * 2;
            d->texture = e->texture;
            
            d->rect.x = x;
            d->rect.y = y;
            d->rect.w = w;
            d->rect.h = h;
        }
    }
}

static void draw() {
    drawBackground();
    drawStarField();
    drawFighter();
    drawBullet();
    drawExplosion();
    drawDebris();
    drawHud();
}

static void drawBackground() {
    SDL_Rect dest;
    int x;
    
    for (x = backgroundX; x < SCREEN_WIDTH; x+= SCREEN_WIDTH) {
        dest.x = x;
        dest.y = 0;
        dest.w = SCREEN_WIDTH;
        dest.h = SCREEN_HEIGHT;
        
        SDL_RenderCopy(app.renderer, background, NULL, &dest);
    }
}

static void drawStarField() {
    int i, c;
    for (i = 0; i < MAX_STARS; i++) {
        c = 32 * star[i].speed;
        SDL_SetRenderDrawColor(app.renderer, c, c, c, 255);
        SDL_RenderDrawLine(app.renderer, star[i].x, star[i].y, star[i].x + 3, star[i].y);
    }
}

static void drawExplosion() {
    Explosion* e;
    SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_ADD);
    SDL_SetTextureBlendMode(explosionTexture, SDL_BLENDMODE_ADD);
    
    for (e = stage.explosionHead.next; e!= NULL; e = e->next) {
        SDL_SetTextureColorMod(explosionTexture, e->r, e->g, e->b);
        SDL_SetTextureAlphaMod(explosionTexture, e->a);
        
        blit(explosionTexture, e->x, e->y);
    }
    SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);
}

static void drawDebris() {
    Debris* d;
    for (d = stage.debrisHead.next; d != NULL; d = d->next) {
        blitRect(d->texture, &d->rect, d->x, d->y);
    }
}

static void drawFighter() {
    Entity* e;
    for (e = stage.fighterHead.next; e != NULL; e = e->next) {
        blit(e->texture, e->x, e->y);
    }
}

static void drawBullet() {
    Entity* b;
    for (b = stage.bulletHead.next; b != NULL; b = b->next) {
        blit(b->texture, b->x, b->y);
    }
}

//TODO: add
static void drawHud() {
    drawText("SCORE: ", 32, 10, 10);
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