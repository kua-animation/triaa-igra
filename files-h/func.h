#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <SDL2/SDL.h>

int colors(int col, int row, int color[row][col], char *name);

int _move_Wheel(int position, SDL_Event event, int speed);

int _move_Click(int position, SDL_Event event, int speed, int botton);


int _move_Hold(int position, int speed, int botton);
#endif
