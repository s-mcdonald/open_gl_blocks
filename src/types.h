#pragma once

#include <vector>

#ifndef BLOCKS_TYPES_H 
#define BLOCKS_TYPES_H

typedef struct RGB {
    short red, green, blue;
  
    RGB() { } // leaving contents uninitialized
    RGB(short red, short green, short blue):
      red(red), green(green), blue(blue)
    { }
 } RGB;

/**
 * The point struct to help us identify 
 * where to spawn blocks ect.
 */
typedef struct {
    int x, y;
} Point;


/**
 * The point struct to help us identify 
 * where to spawn blocks ect.
 */
typedef struct Block {
    Point xy;
    short value;
    bool is_enemy = false;
} Block;


/**
 * The point struct to help us identify 
 * where to spawn blocks ect.
 */
typedef struct {
    bool game_over = false;
    bool game_started = false;
} GameState;

extern GameState gameState;

typedef struct {
    bool spawnFriend = false;
    bool spawnEnemy = false;
} GameAction;

extern GameAction gameAction;
extern std::vector<Block> spawners;

#endif /* BLOCKS_TYPES_H */