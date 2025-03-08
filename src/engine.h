#pragma once

#include "types.h"

#ifndef BLOCKS_ENGINE_H 
#define BLOCKS_ENGINE_H

namespace SamMcDonald::Blocks {

    void doClearScreen();

    void doStartGame();

    void doGameOver();

    void doSpawnBlock(Point p);

    /**
     * Use oGL to display text on screen ;;
     */
    void doDrawText(const char* text, Point p);

}

#endif /* BLOCKS_ENGINE_H */