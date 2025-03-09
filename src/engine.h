#pragma once

#include "types.h"

#ifndef BLOCKS_ENGINE_H 
#define BLOCKS_ENGINE_H

namespace SamMcDonald::Blocks {

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
}

#endif /* BLOCKS_ENGINE_H */