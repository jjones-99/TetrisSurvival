*A Project for Programming in C++*  
*Code by Jared Jones, Will Bridges, and Tommy O'Hara*  
*Graphics by Jared Jones*

# Tetris Survival

This is a simple survival game based on the popular game of Tetris.

In ordinary Tetris, you control the tetrominos that fall, rotating and moving them in an attempt to fit them together and survive for as long as possible without reaching the top.

In Tetris Survival, those blocks are randomly generated, and don't move after they spawn at the top of the screen. Instead, you control an avatar. In this case, the avatar is a smaller block that moves around the screen, affected by gravity. The goal of the game is to survive long enough to reach the top of the screen.

## Beginning a Game

The game can be compiled on the command line using the command `make`, and can be run using the command `./main`.

The game opens to the main menu, where you can either play or quit. If you hit play, you must enter configuration options. The board width, board height, cell size (the graphical size of each cell), and difficulty (how quickly you move and blocks fall). These must all be non-negative integers. Press enter to confirm each option and move on to the next. After you confirm every option, the game will start. We recommend starting with a board size of 10x10, a cell size of 25, and a difficulty of 1. After that, fiddle with them until you find a fun combination.

## Controls

To play the game, use the following keys:
- Up: Jump
- Left: Move left
- Right: Move right
- Esc: Quit early

## Winning

The game will end in a loss if you are crushed by a block. The game will end in a win if you jump above the game window.
