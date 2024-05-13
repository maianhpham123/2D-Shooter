//
//  init.hpp
//  2D Shooter
//
//  Created by Mai Anh Pham on 5/6/24.
//

#ifndef init_hpp
#define init_hpp

#include "commons.h"

static void initBackground();
static void initStarField();
static void initSound();
static void loadMusic(const char* filename);
static void playMusic(int loop);

extern App app;

#endif /* init_hpp */
