#pragma once

#include "types.h"

#ifndef BLOCKS_ENGINE_H 
#define BLOCKS_ENGINE_H

namespace SamMcDonald::Blocks {

    
    void doStartGame();

    void doGameOver();

    /**
     * Use oGL to display text on screen ;;
     */
    void doDrawText(const char* text, Point p);

}

#endif /* BLOCKS_ENGINE_H */