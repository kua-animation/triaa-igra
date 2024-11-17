#ifndef PLAYER_H
#define PLAYER_H

#include "../struct/struct.h"
#define BOUNCE 1
#define NO_BOUNCE 0
int collisionRect(Player *name, Rect *rect, int *speed, int bounce);

void collisionScrine(Player *name, int scrineHeight, int scrineWidth, int *speed);

int collisionWindow(Player *name, Window *window, int *speed, int bounce);

void setPlayerSide(Player *name);


#endif