#pragma once

#ifndef BLOCKS_TYPES_H 
#define BLOCKS_TYPES_H

/**
 * The point struct to help us identify 
 * where to spawn blocks ect.
 */
typedef struct Point {
    int x, y;
} Point;


/**
 * The point struct to help us identify 
 * where to spawn blocks ect.
 */
typedef struct Block {
    Point xy;
    short value;
} Block;

/**
 * The point struct to help us identify 
 * where to spawn blocks ect.
 */
typedef struct GameState {
    bool game_over = false;
    bool game_started = false;
} GameState;

#endif /* BLOCKS_TYPES_H */