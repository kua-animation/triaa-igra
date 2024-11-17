#include "../files-h/drawline.h"
#include "../files-h/createWindow.h"


void _drawPlayer(int positionX, int positionY, int speed, int color[4], SDL_Renderer *renderer, int PlayerWidth, int PlayerHeight){
    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], color[3]);
    SDL_Point a = {positionX,positionY}, b = {positionX + PlayerWidth ,positionY}, c = {positionX + PlayerWidth/2,positionY - PlayerHeight };
    SDL_RenderDrawLine(renderer, a.x, a.y, b.x, b.y);
    SDL_RenderDrawLine(renderer, a.x, a.y, c.x, c.y);
    SDL_RenderDrawLine(renderer, c.x, c.y, b.x, b.y);
}

void _rectelgle(int positionX, int positionY, int height, int width, int addPositionX, int addPositionY, int color[4], SDL_Renderer *renderer, int PlayerSizeX, int PlayerSizeY){
    if (addPositionX +PlayerSizeX > positionX && addPositionY +PlayerSizeY > positionY && addPositionX < positionX + width && addPositionY < positionY + height  ){ 
    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], color[3]);
    SDL_Rect rect = {positionX - addPositionX, positionY - addPositionY, width, height};
    SDL_RenderDrawRect(renderer, &rect);
    }
}

void render(Player *name, int speed, int color[4][4], SDL_Renderer *renderer[], Rect *rect){

}

