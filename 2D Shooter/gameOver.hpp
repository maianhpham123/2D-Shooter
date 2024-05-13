//
//  gameOver.hpp
//  2D Shooter
//
//  Created by Mai Anh Pham on 5/12/24.
//

#ifndef gameOver_hpp
#define gameOver_hpp

#include "commons.h"

static void doBackground();
static void doStarField();
static void initStage();
static void drawBackground();
static void drawStarField();
void drawText(const char* text, int size, int x, int y);

extern App app;
extern Stage stage;
#endif /* gameOver_hpp */
