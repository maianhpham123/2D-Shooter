//
//  main.hpp
//  2D Shooter
//
//  Created by Mai Anh Pham on 5/6/24.
//

#ifndef main_hpp
#define main_hpp

#include "commons.h"

#include "init.cpp"
#include "input.cpp"
#include "draw.cpp"
#include "stage.cpp"

extern void initSDL();
extern void cleanup();
extern void prepareScene();
extern void doInput();
extern void presentScene();

App app;
Stage stage;

#endif /* main_hpp */
