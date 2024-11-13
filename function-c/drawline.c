#include "../function-h/drawline.h"
#include "../function-h/window.h"


void player(int positionX, int positionY, int speed, int color[4], SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], color[3]);
    SDL_Point a = {positionX,positionY}, b = {positionX + 60 ,positionY}, c = {positionX + 30 - speed,positionY + speed * 2};
    SDL_RenderDrawLine(renderer, a.x, a.y, b.x, b.y);
    SDL_RenderDrawLine(renderer, a.x, a.y, c.x, c.y);
    SDL_RenderDrawLine(renderer, c.x, c.y, b.x, b.y);
}

void _rectelgle(int positionX, int positionY, int height, int width, int addPositionX, int addPositionY, int color[4], SDL_Renderer *renderer){
    if (addPositionX +260 > positionX && addPositionY +260 > positionY && addPositionX < positionX + width && addPositionY < positionY + height  ){ 
    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], color[3]);
    SDL_Rect rect = {positionX - addPositionX, positionY - addPositionY, width, height};
    SDL_RenderDrawRect(renderer, &rect);
    }
}