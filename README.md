# 2048-game
Developed a version of the classic 2048 game in C(using the ncurses library) featuring the functions to move the tiles in order to connect them and reach the target score, as well as a function that makes the most efficient move if the user doesn't make a decision in a few seconds.
![image](https://github.com/user-attachments/assets/99699ab3-29ec-40ec-9204-b16d63d1018f)
# Prerequisites
**C Compiler**: Ensure that a C compiler like gcc is installed.

**ncurses library**: The game uses the ncurses library for terminal-based user interfaces.

```sh
sudo apt-get install libncurses5-dev libncursesw5-dev
```
# Instalation
``` sh
git clone https://github.com/Ioana-Maraloi/2048-game.git
cd 2048-game
make
./2048-game
```
# How to play
**Objective:** The goal of the game is to combine tiles with the same number to reach the number 2048.

**Controls:** Use the arrow keys to move the tiles on the grid. When two tiles with the same number touch, they merge into one.

**Automatic Move**: If you don't make a move within a few seconds, the game will make the most efficient move for you.

**Winning**: You win the game when you create a tile with the number 2048.

**Game Over**: The game is over when there are no possible moves left.
