#include <iostream>
#include <vector>

#include <GL/glut.h>

#include <GL/glx.h>

#include "constants.h"
#include "engine.h"
#include "types.h"
#include "keys.h"

namespace SamMcDonald::Blocks {

    // found vertex buffer might help with rendering
    // https://en.wikipedia.org/wiki/Vertex_buffer_object
    // https://www.khronos.org/opengl/wiki/Buffer_Object
    GLuint vbo;

    // Function pointers for VBO-related functions api entry points
    PFNGLGENBUFFERSARBPROC glGenBuffers = nullptr;
    PFNGLBINDBUFFERARBPROC glBindBuffer = nullptr;
    PFNGLBUFFERDATAARBPROC glBufferData = nullptr;

    /**
     * Load openGLs vertext buffer functions so we dont need GLad.
     * we should prob extract this to a diff cpp file/namespace
     */
    void loadGLVBOFunctions() {
        glGenBuffers = (PFNGLGENBUFFERSARBPROC)glXGetProcAddressARB((const GLubyte*)"glGenBuffers");
        glBindBuffer = (PFNGLBINDBUFFERARBPROC)glXGetProcAddressARB((const GLubyte*)"glBindBuffer");
        glBufferData = (PFNGLBUFFERDATAARBPROC)glXGetProcAddressARB((const GLubyte*)"glBufferData");

        if (!glGenBuffers || !glBindBuffer || !glBufferData) {
            std::cerr << "Failed to load VBO functions" << std::endl;
            exit(1);
        }
    }

    void initializeVertexBufferObject() {
        glGenBuffers(1, &vbo);
    }

    void updateVertexBufferObject(const std::vector<Block>& spawners) {
        std::vector<GLfloat> vertices;
        for (const auto& spawner : spawners) {
            GLfloat x = static_cast<GLfloat>(spawner.xy.x);
            GLfloat y = static_cast<GLfloat>(spawner.xy.y);
            GLfloat size = static_cast<GLfloat>(BLOCK_SIZE);

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(x + size);
            vertices.push_back(y);
            vertices.push_back(x + size);
            vertices.push_back(y + size);
            vertices.push_back(x);
            vertices.push_back(y + size);
        }

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_DYNAMIC_DRAW);
    }

    void updateVertexBufferObject(const Block& spawner) {
        std::vector<GLfloat> vertices;

        GLfloat x = static_cast<GLfloat>(spawner.xy.x);
        GLfloat y = static_cast<GLfloat>(spawner.xy.y);
        GLfloat size = static_cast<GLfloat>(BLOCK_SIZE);

        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(x + size);
        vertices.push_back(y);
        vertices.push_back(x + size);
        vertices.push_back(y + size);
        vertices.push_back(x);
        vertices.push_back(y + size);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_DYNAMIC_DRAW);
    }

    void renderVBO() {
        glEnableClientState(GL_VERTEX_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexPointer(2, GL_FLOAT, 0, nullptr);
        glDrawArrays(GL_QUADS, 0, spawners.size() * 4);
        glDisableClientState(GL_VERTEX_ARRAY);
    }

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

    void doSpawnBlock(const Block& spawner)
    {
        glColor3f(1.0f, 0.0f, 0.0f);

        glBegin(GL_QUADS);
        glVertex2i(spawner.xy.x, spawner.xy.y);
        glVertex2i(spawner.xy.x + BLOCK_SIZE, spawner.xy.y);
        glVertex2i(spawner.xy.x + BLOCK_SIZE, spawner.xy.y + BLOCK_SIZE);
        glVertex2i(spawner.xy.x, spawner.xy.y + BLOCK_SIZE);
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

        // // Game has started!
        if (gameState.game_started == true && gameState.game_over == false ) {
            switch(key) {
                case GAME_KEY_S:
                case GAME_KEY_s:
                    srand(time(0));
                    std::cout << "Spawn " << std::endl;
                    Point spawn_location; // we need to randomly generate these
                    spawn_location.x = (rand() % (WIDTH / BLOCK_SIZE)) * BLOCK_SIZE;
                    spawn_location.y = (rand() % (HEIGHT / BLOCK_SIZE)) * BLOCK_SIZE;
                    Block spawner;
                    spawner.xy = spawn_location;
                    spawner.value = 100;
                    spawners.push_back(spawner);

                    updateVertexBufferObject(spawners);
                    glutPostRedisplay();
                    break;
            }
        }
    }
}