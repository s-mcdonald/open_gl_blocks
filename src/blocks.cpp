
/******************************************************************************
 * MIT License
 * 
 * Copyright (c) 2025 Sam McDonald
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * provided to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * -----------------------------------------------------------------------------
 * 
 * Author: Sam McDonald
 * Date: 2025-03-09
 * 
 *****************************************************************************/

#include <iostream>

#include "engine.h"

/**
 * Game environment constants.
 */
const int WIDTH = 800;
const int HEIGHT = 600;

const char* game_title = "Blocks";

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
} GameState;


int main(int argc, char** argv) {

    SamMcDonald::Blocks::doStartGame();

    SamMcDonald::Blocks::doGameOver();

}