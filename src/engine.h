#pragma once

#include "types.h"

#ifndef BLOCKS_ENGINE_H 
#define BLOCKS_ENGINE_H

namespace SamMcDonald::Blocks {

    /// 
    /// VBuffs
    ///

    void loadGLVBOFunctions();

    void initializeVertexBufferObject();

    void updateVertexBufferObject(const std::vector<Block>& spawners);

    void renderVBOSpawners();

    /// 
    /// Game code
    ///


    void doClearScreen();

    void doStartGame();

    void doGameOver();

    void doSpawnBlock(const Block& spawner);

    /**
     * Use oGL to display text on screen ;;
     */
    void doDrawText(const char* text, Point p);

    void handleSpecialKeypress(int key, int x, int y);

    void handleKeypress(unsigned char key, int x, int y);


    ///
    /// Collision Detection
    ///
    bool pointWillCollide(Point p);

    void doCollisionAnimation();
}

#endif /* BLOCKS_ENGINE_H */