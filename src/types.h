#pragma once

#include <vector>

#ifndef BLOCKS_TYPES_H 
#define BLOCKS_TYPES_H

struct RGB {
    uint8_t red, green, blue;
  
    RGB() { } // leaving contents uninitialized
    RGB(uint8_t red, uint8_t green, uint8_t blue):
      red(red), green(green), blue(blue)
    { }
  };

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
} Block;

typedef struct Enemy: Block {
    RGB color = {1.0f, 0.0f, 0.0f};
} Block;

typedef struct Friend: Block {
    RGB color = {0.0f, 0.0f, 1.0f};
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