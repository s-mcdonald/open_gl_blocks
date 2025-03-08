
/******************************************************************************
 * MIT License
 * 
 * Copyright (c) 2025 Sam McDonald
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * provided to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * -----------------------------------------------------------------------------
 * 
 * Author: Sam McDonald
 * Date: 2025-03-09
 * 
 *****************************************************************************/

#include <iostream>

#include <GL/glut.h>
#include <ctime>

#include "engine.h"
#include "types.h"
#include "constants.h"


// initial the game state ;;
GameState gameState;
short game_execution_time = 0;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (gameState.game_over) {
        SamMcDonald::Blocks::doGameOver();
        glutSwapBuffers();
        return;
    }

    // we need a new calc for center, need to take into
    // account the length of the text. Text size could
    // prob do with change also as screen is resized.
    Point p;
    p.x = WIDTH / 2 - 50;
    p.y = HEIGHT / 2;

    // Game window is showing but no text on screen yet, thats because
    // the game is not over and we have nothing to render.
    // While I dev, ill print some text to the screen.
    // In the GameState we can add a new flag "game_started"
    if (gameState.game_started) {
        SamMcDonald::Blocks::doDrawText("Game has started", p);
    } else {
        SamMcDonald::Blocks::doDrawText("Game not started", p);
    }

    // still need to call this if not game over for now.
    glutSwapBuffers();
}

/**
 * Prob only useful for dev. This will timeout
 * the clock so we can end the game.
 */
void game_timer(int value) {
    game_execution_time++;
    if (game_execution_time >= 3) {
        gameState.game_over = true;
        SamMcDonald::Blocks::doGameOver();
        glutSwapBuffers();
    } else {
        glutTimerFunc(1000, game_timer, 0);
    }
}


int main(int argc, char** argv) {

    SamMcDonald::Blocks::doStartGame();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow(game_title);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT);

    glutDisplayFunc(display);

    glutTimerFunc(GAME_INTERVAL, game_timer, 0);

    glutMainLoop();
    
    SamMcDonald::Blocks::doGameOver();

    //return 0; // auto return
}