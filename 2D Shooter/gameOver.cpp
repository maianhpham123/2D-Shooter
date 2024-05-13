//
//  gameOver.cpp
//  2D Shooter
//
//  Created by Mai Anh Pham on 5/12/24.
//

#include "gameOver.hpp"

static void gameOverLogic();
static void gameOverDraw();
static void drawScore(int score, int highScore);

static int timeout;

void initGameOver() {
    app.delegate.logic = gameOverLogic;
    app.delegate.draw = gameOverDraw;
    
    memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);
    
    timeout = FPS * 5;
}

static void gameOverLogic() {
    doBackground();
    doStarField();
    
    if (--timeout <= 0) {
        initGameOver();
    }
    
    if(app.keyboard[SDL_SCANCODE_LSHIFT]) {
        initStage();
    }
}

static void gameOverDraw() {
    drawBackground();
    drawStarField();
    drawScore(stage.score, stage.highScore); //TODO: change score
}

static void drawScore(int score, int highScore) {
    const char *text1, *text2;
    char scoreText[20];
    char highscoreText[20];
    
    text1 = "SCORE: ";
    text2 = "HIGHSCORE: ";
    
    sprintf(scoreText, "%s %d", text1, score);
    sprintf(highscoreText, "%s %d", text2, highScore);
    drawText(scoreText, 50, 425, 230);
    drawText(highscoreText, 50, 425, 330);
    
    drawText("PRESS FIRE TO PLAY!", 32, 425, 600);
}
