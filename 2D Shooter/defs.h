//
//  defs.h
//  2D Shooter
//
//  Created by Mai Anh Pham on 5/6/24.
//

#ifndef defs_h
#define defs_h

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
const char* WINDOW_TITLE = "SHOOTER";

#define PLAYER_SPEED 4
#define PLAYER_BULLET_SPEED 16
#define ALIEN_BULLET_SPEED 8

#define MAX_KEYBOARD_KEYS 350

#define SIDE_PLAYER 0
#define SIDE_ALIEN 1

#define FPS 60

#define MAX_STARS 500

#define MAX_SND_CHANNELS 8

#define STRNCPY(dest, src, n) strncpy(dest, src, n); dest[n-1] = '\0'
#define MAX_NAME_LENGTH 32

enum {
    CH_ANY = -1,
    CH_PLAYER,
    CH_ALIEN_FIRE,
    CH_POINT
};

enum {
    SND_PLAYER_FIRE,
    SND_ALIEN_FIRE,
    SND_PLAYER_DIE,
    SND_ALIEN_DIE,
    SND_POINT,
    SND_MAX
};

#endif /* defs_h */
