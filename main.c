
#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <stdlib.h>
#include "function-h/window.h"
#include "function-h/drawline.h"
#include "function-h/color.h"


int texter[16][16] = {
	{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
	{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
	{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
	{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
	{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
	{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
	{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
	{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
	{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1}
};



int _move_Wheel(int position, SDL_Event event, int speed){
    if (event.type == SDL_MOUSEWHEEL){
        if (event.wheel.y > 0){
            position -= speed;
        } else if (event.wheel.y < 0){
            position += speed;
        }
    }
    return position;
}


int _move_Click(int position, SDL_Event event, int speed, int botton){
    if (event.type == SDL_MOUSEBUTTONDOWN){
        if (event.button.button == botton){
            position -= speed;
        }
    }
    return position;
}


int _move_Hold(int position, int speed, int botton){
    Uint32 mouseState = SDL_GetMouseState(NULL, NULL);
    if (mouseState & SDL_BUTTON(botton)){
        position -= speed;
    }
    return position;
}




void _render(int color[2][4], int posX, int posY, int speed){
    SDL_SetRenderDrawColor(renderer, color[1][0], color[1][1], color[1][2], color[1][3]);
	SDL_RenderClear(renderer);
        

    SDL_Point a = {200,200}, b = {300,200}, c = {250 - speed,100};
    SDL_RenderDrawLine(renderer, a.x, a.y, b.x, b.y);
    SDL_RenderDrawLine(renderer, a.x, a.y, c.x, c.y);
    SDL_RenderDrawLine(renderer, c.x, c.y, b.x, b.y);
    
    SDL_RenderPresent(renderer);
}






int main() {
    int row = 2;
    int Color[row][4];
    colors(row,4, Color);
    int speed = 0;
    int posX = 50;
    int posY = 10; 
    int maxPos = 30;

    if (_createWindow() != 0) {
        return 1;
    }

    
    SDL_Event event;
    int running = 1;
    FILE *draw = fopen( "draw.txt", "w");

    if(draw == NULL){
        printf("fill not working");
        return 1;
    } 

    

    

    while (running){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT) {
                running = 0;
                
            }
            speed = _move_Wheel(speed, event, 1);
            if (speed > maxPos){
                speed = maxPos;
            } else if (speed < -maxPos){
                speed = -maxPos;
            }
            if (speed != posY || speed != posX){
                fprintf(draw, "%d", speed);
                }

            posY = _move_Click(posY, event,  -speed, 3);
            posX = _move_Click(posX, event, speed, 1);


            _render(Color, posX, posY, speed);

        }
        SDL_Delay(10);
    }
    fclose(draw);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();


    return 0;
}

