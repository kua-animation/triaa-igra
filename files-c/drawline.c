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

void render(Player *name, int speed, int color[4][4], SDL_Renderer *renderer[]){

    // Render  Window1
    SDL_SetRenderDrawColor(renderer[0], color[1][0], color[1][1], color[1][2], color[1][3]);
    SDL_RenderClear(renderer[0]);

    // player render 
    _drawPlayer(name->window.Width/2 - name->scale.Width/2,name->window.Height/2 + name->scale.Height/2 ,speed ,color[0],renderer[0], name->scale.Width, name->scale.Height);

    // world render 
    _rectelgle(500,500,200,200,name->position.x,name->position.y, color[3], renderer[0], name->window.Width, name->window.Width);
    _rectelgle(550,550,100,100,name->position.x,name->position.y, color[3], renderer[0], name->window.Width, name->window.Height);
    _rectelgle(450,450,300,300,name->position.x,name->position.y, color[3], renderer[0], name->window.Width, name->window.Height);

    SDL_RenderPresent(renderer[0]);

    SDL_SetRenderDrawColor(renderer[2], color[2][0], color[2][1], color[2][2], color[2][3]);
    SDL_RenderClear(renderer[2]);

    SDL_RenderPresent(renderer[2]);


    // Render Window2
    SDL_Delay(10);
}

