#ifndef DRAWLINE_H
#define DRAWLINE_H

#define ANGLE_HORIZONT 1
#define ANGLE_VERTICAL 2
#define ANGLE_DIAGONAL_POS 3
#define ANGLE_DIAGONAL_NEG -3
#define ANGLE_DIAGONAL_POS_ALT 4
#define ANGLE_DIAGONAL_NEG_ALT -4


#include <SDL2/SDL.h>
#include <stdio.h>

void player(int positionX, int positionY, int speed, int color[4], SDL_Renderer *renderer);


#endif
