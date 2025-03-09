
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


short game_execution_time = 0;

void display() {
    // Refresh the screen buffer
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (gameState.game_over) {
        SamMcDonald::Blocks::doGameOver();
        glutSwapBuffers();
        glutPostRedisplay();
        return;
    }

    // we need a new calc for center, need to take into
    // account the length of the text. Text size could
    // prob do with change also as screen is resized.
    Point p_center_screen;
    p_center_screen.x = WIDTH / 2 - 50;
    p_center_screen.y = HEIGHT / 2;

    // game not started
    if (gameState.game_started == false && gameState.game_over == false) {
        glColor3f(0.0f, 1.0f, 0.0f);
        SamMcDonald::Blocks::doDrawText("Press any key to begin", p_center_screen);
        glutSwapBuffers();
        glutPostRedisplay();
        return;
    }

    // in game play here
    if (gameState.game_started && gameState.game_over == false) {
        SamMcDonald::Blocks::doDrawText("Game has started", p_center_screen);
        Point p;
        p.x = 140;
        p.x = 150;
        SamMcDonald::Blocks::doSpawnBlock(p);
        glutSwapBuffers();
        glutPostRedisplay();
        return;
    }

    // Game ended
    if (gameState.game_started && gameState.game_over == true) {
        glColor3f(1.0f, 0.0f, 0.0f);
        SamMcDonald::Blocks::doDrawText("Game Over", p_center_screen);
        glutSwapBuffers();
        return;
    }

    SamMcDonald::Blocks::doDrawText("This is something else", p_center_screen);
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

    // we could introduce this later for time control,
   // glutTimerFunc(GAME_INTERVAL, game_timer, 0);

    glutDisplayFunc(display);
    glutKeyboardFunc(SamMcDonald::Blocks::handleKeypress); 

    glutMainLoop();
    SamMcDonald::Blocks::doGameOver();

    //return 0; // auto return
}