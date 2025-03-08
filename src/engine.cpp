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
}