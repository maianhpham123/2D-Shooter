//
//  main.cpp
//  2D Shooter
//
//  Created by Mai Anh Pham on 5/6/24.
//

#include "main.hpp"

int main(int argc, char* argv[])
{
    long then;
    float remainder;
    
    memset(&app, 0, sizeof(App));
    memset(&stage, 0, sizeof(Stage));
    
    initSDL();
    atexit(cleanup);
    initStage();
    
    then = SDL_GetTicks();
    remainder = 0;
    
    while (1) {
        prepareScene();
        doInput();
        
        app.delegate.logic();
        app.delegate.draw();
        
        presentScene();
        
        capFrameRate(&then, &remainder);
    }
    
    return 0;
}
