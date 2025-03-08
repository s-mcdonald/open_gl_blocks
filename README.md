# Blocks ;;

##### Game Engine
I have decided to turn his project into a mini game engine.
For now ill keep calling this blocks until I have a better name;;

###### Objectives
* The game engine will soley focus on block based games
* It will provide a framwork for basic game control and flow control
* The engine will provide a selection of "spawner" that can be used in games
* Additionally, games can create their own spawners;
* Over time I will decide more features, I know its a bit rough around the edges but a game engine is a good way to learn game dev so thats what ill do!



##### About
Blocks is my first OpenGL program to help me learn about OGL, rendering and some basic game development using c++.
I have designed this in such a way I can expand from the initial `Blocks` environment to build the next
game which will be my version of `Snakes` called `Jungle Python`.

So Blocks will implement a 2D flat plane in which blocks will spawn.
To consider the Snakle game on how I want to build it, the Blocks will have a specific behaviour
to how I want the Snakes game to work.

* Blocks can spawn randomly
* Blocks can be 1 of 3 colours
* Each colour containing a value
    * Red = 1 
    * Yellow = 2
    * Blue = 3
* Multiple Blockis Can spawn
* Red Blocks have a lifetime (min 1 second)
* Blocks can not spawn on or adjacent to other blocks


To end the environment F1 to call game over.

Note that Blocks is not a game, refer to my snakes game.