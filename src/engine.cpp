#include <iostream>
#include <vector>
#include <random>
#include <typeinfo>

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

            // Add vertex positions and color information
            GLfloat r = spawner.is_enemy ? 1.0f : 0.0f;
            GLfloat g = 0.0f;
            GLfloat b = spawner.is_enemy ? 0.0f : 1.0f;

            // Bottom-left
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(r);
            vertices.push_back(g);
            vertices.push_back(b);

            // Bottom-right
            vertices.push_back(x + size);
            vertices.push_back(y);
            vertices.push_back(r);
            vertices.push_back(g);
            vertices.push_back(b);

            // Top-right
            vertices.push_back(x + size);
            vertices.push_back(y + size);
            vertices.push_back(r);
            vertices.push_back(g);
            vertices.push_back(b);

            // Top-left
            vertices.push_back(x);
            vertices.push_back(y + size);
            vertices.push_back(r);
            vertices.push_back(g);
            vertices.push_back(b);
            
        }
    
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    }

    void renderVBOSpawners() {
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        // Set the vertex pointer
        glVertexPointer(2, GL_FLOAT, 5 * sizeof(GLfloat), (void*)0);

        // Set the color pointer
        glColorPointer(3, GL_FLOAT, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

        // Draw each block
        for (size_t i = 0; i < spawners.size(); ++i) {
            glDrawArrays(GL_QUADS, i * 4, 4);
        }

        glDisableClientState(GL_COLOR_ARRAY);
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

    void doDrawText(const char* text, Point p) {
        glRasterPos2i(p.x, p.y);
        while (*text) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
            text++;
        }
    }

    /**
     * GLUT API macro definitions --  https://www.glfw.org/docs/3.3/group__keys.html
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
                    auto is_friend = ((rand() % 2) + 1 ==  2);

                    srand(time(0));
                    std::cout << "Spawn " << std::endl;
                    Point spawn_location; // we need to randomly generate these
                    spawn_location.x = (rand() % (WIDTH / BLOCK_SIZE)) * BLOCK_SIZE;
                    spawn_location.y = (rand() % (HEIGHT / BLOCK_SIZE)) * BLOCK_SIZE;

                    Block spawner;
                    spawner.xy = spawn_location;
                    spawner.value = is_friend ? 100 : -200;
                    spawner.is_enemy = !is_friend;

                    spawners.push_back(spawner);
                    updateVertexBufferObject(spawners);
                    glutPostRedisplay();
                    break;
            }
        }
    }

    bool pointWillCollide(Point p)
    {
        return true;
    }

    void doCollisionAnimation()
    {
        //
    }
}