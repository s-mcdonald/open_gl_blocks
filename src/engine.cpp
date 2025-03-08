#include <iostream>
#include <GL/glut.h>

#include "engine.h"
#include "types.h"

namespace SamMcDonald::Blocks {

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

    void doDrawText(const char* text, Point p) {
        glRasterPos2i(p.x, p.y);
        while (*text) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
            text++;
        }
    }
}