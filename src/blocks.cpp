
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
        return;
    }

    // we need a new calc for center, need to take into
    // account the length of the text. Text size could
    // prob do with change also as screen is resized.
    Point p_center_screen;
    p_center_screen.x = WIDTH / 2 - 50;
    p_center_screen.y = HEIGHT / 2;

    // game not started
    if (false == gameState.game_started && false == gameState.game_over) {
        glColor3f(0.0f, 1.0f, 0.0f);
        SamMcDonald::Blocks::doDrawText("Press F1 to start game.", p_center_screen);
        glutSwapBuffers();
        return;
    }

    // in game play here
    if (true == gameState.game_started && false == gameState.game_over) {
        SamMcDonald::Blocks::renderVBO();
        glutSwapBuffers();
        // for (auto s : spawners)
            // SamMcDonald::Blocks::doSpawnBlock(s);
        
        return;
    }

    // Game ended
    if (gameState.game_started && gameState.game_over == true) {
        glColor3f(1.0f, 0.0f, 0.0f);
        SamMcDonald::Blocks::doDrawText("Game Over", p_center_screen);
        glutSwapBuffers();
        return;
    }

    glutSwapBuffers();

}


void game_timer(int value) {
    
    glutPostRedisplay();

    glutTimerFunc(1000, game_timer, 0);
}

void game_timer() {
    
    if (true == gameState.game_over) {
        glutPostRedisplay();
        return;
    }

    glutPostRedisplay();
    glutTimerFunc(100, game_timer, 0);
}


int main(int argc, char** argv) {

    SamMcDonald::Blocks::doStartGame();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Blocks");

    SamMcDonald::Blocks::loadGLVBOFunctions();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT);

    SamMcDonald::Blocks::initializeVertexBufferObject();

    // we could introduce this later for time control,
    //glutTimerFunc(GAME_INTERVAL, game_timer, 0);

    //game_timer();

    glutDisplayFunc(display);
    glutKeyboardFunc(SamMcDonald::Blocks::handleKeypress); 
    glutSpecialFunc(SamMcDonald::Blocks::handleSpecialKeypress);

    glutMainLoop();
    SamMcDonald::Blocks::doGameOver();

    //return 0; // auto return
}