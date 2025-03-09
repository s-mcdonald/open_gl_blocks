#include <iostream>
#include <GL/glut.h>

#include "engine.h"
#include "types.h"
#include "constants.h"

namespace SamMcDonald::Blocks {

    void doClearScreen()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void doStartGame()
    {
        std::cout << "Game Started" << std::endl;
    }

    void doGameOver()
    {
        // Lets bring in the Log lib to handle debug messages later
        std::cout << "Game Over!" << std::endl;

        Point p;
        p.x = WIDTH / 2 - 50;
        p.y = HEIGHT / 2;
        doDrawText("Game Over", p);
    }

    void doSpawnBlock(Point p)
    {
        glColor3f(1.0f, 0.0f, 0.0f);

        glBegin(GL_QUADS);
        glVertex2i(p.x, p.y);
        glVertex2i(p.x + BLOCK_SIZE, p.y);
        glVertex2i(p.x + BLOCK_SIZE, p.y + BLOCK_SIZE);
        glVertex2i(p.x, p.y + BLOCK_SIZE);
        glEnd();
        glutSwapBuffers();
    }


    void doDrawText(const char* text, Point p) {
        glRasterPos2i(p.x, p.y);
        while (*text) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
            text++;
        }
    }

        /**
     * GLUT API macro definitions -- the special key codes:
     *
     * GLUT_KEY_F1                        0x0001
     * GLUT_KEY_F2                        0x0002
     * GLUT_KEY_F3                        0x0003
     * GLUT_KEY_F4                        0x0004
     * GLUT_KEY_F5                        0x0005
     * GLUT_KEY_F6                        0x0006
     * GLUT_KEY_F7                        0x0007
     * GLUT_KEY_F8                        0x0008
     * GLUT_KEY_F9                        0x0009
     * GLUT_KEY_F10                       0x000A
     * GLUT_KEY_F11                       0x000B
     * GLUT_KEY_F12                       0x000C
     * GLUT_KEY_LEFT                      0x0064
     * GLUT_KEY_UP                        0x0065
     * GLUT_KEY_RIGHT                     0x0066
     * GLUT_KEY_DOWN                      0x0067
     * GLUT_KEY_PAGE_UP                   0x0068
     * GLUT_KEY_PAGE_DOWN                 0x0069
     * GLUT_KEY_HOME                      0x006A
     * GLUT_KEY_END                       0x006B
     * GLUT_KEY_INSERT                    0x006C
     */

    void handleSpecialKeypress(int key, int x, int y) {

        std::cout << "Key Pressed: " << key << std::endl;

        // Game not started
        if (false == gameState.game_started && false == gameState.game_over) {
            switch (key) {
                case GLUT_KEY_F1:
                    std::cout << "Signal to start game.. " << std::endl;
                    gameState.game_started = true;
                    
                    break;
            }

            glutPostRedisplay();
            return;
        }

        // In game play
        if (true == gameState.game_started && false == gameState.game_over) {
            switch (key) {
                case GLUT_KEY_F1:
                    std::cout << "Signal to end game.. " << std::endl;
                    gameState.game_over = true;
                    break;
            }
            glutPostRedisplay();
        }
    }


    void handleKeypress(unsigned char key, int x, int y) {

        std::cout << "Key Pressed: " << key << std::endl;

        // Start the game!
        // if (gameState.game_started == false && gameState.game_over == false ) {
        //     gameState.game_started == true;
        //     return;
        // }

        // if (gameState.game_started == false && gameState.game_over == true ) {
        //     // something went wrong
        //     //exit(0);
        // }

        // // Game has started!
        // if (gameState.game_started == true && gameState.game_over == false ) {
        //     // switch(key) {

        //     //         break;
        //     // }
        //     return;
        // }

        // // game has ended, so any key sghould close the game
        // if (gameState.game_started == true && gameState.game_over == true) {
        //    // exit(0);
        // }

        //std::cout << "Why are we here...\n";
    }
}