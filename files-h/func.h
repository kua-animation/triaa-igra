#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include "../struct/struct.h"

int colors(int col, int row, int color[row][col], char *name);

int _move_Wheel(int position, SDL_Event event, int speed);

int _move_Click(int position, SDL_Event event, int speed, int botton);

int _move_Hold(int position, int speed, int botton);

void SetRectSide(Rect *rect);

int _move(Player *player, int speed, int botton, SDL_Event event);
#endif
