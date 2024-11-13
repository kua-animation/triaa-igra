
#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <stdlib.h>
#include "function-h/window.h"
#include "function-h/drawline.h"
#include "function-h/color.h"

SDL_Window *Window[2];
SDL_Renderer *Renderer[2];


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


int main() {
    int row = 3;
    int Color[row][4];
    colors(row,4, Color);
    int posX = 0;
    int posY = 100;  
    int speed = 0;
    int index = 0;


    if (createWindow(&Window[0], &Renderer[0], 260,260, posX,20) != 0) {
        return 1;
    }
    if (createWindow(&Window[1], &Renderer[1], 250, 600, 1920 - 250,0) != 0) {
        SDL_DestroyRenderer(Renderer[0]);
        SDL_DestroyWindow(Window[0]);
        SDL_Quit();
        return 1;
    }
    SDL_Event event;
    int running = SDL_TRUE;

    while (running){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = SDL_FALSE;
                }
            }
            speed = _move_Wheel(speed, event, 2);
            
            
            if (speed > 5){speed = 5;}
            else if (speed < -5){speed = -5;} 
            
            if (posX > 1920 - 260){posX = 0;}
            else if (posX < 0){posX = 1920 - 260;}
            posX -= speed;
        }
        SDL_SetWindowPosition(Window[0], posX, 0);
        SDL_SetWindowAlwaysOnTop(Window[0], SDL_TRUE);
       

        // Render  Window1
        SDL_SetRenderDrawColor(Renderer[0], Color[1][0], Color[1][1], Color[1][2], Color[1][3]);
        SDL_RenderClear(Renderer[0]);
        player(100,120,speed * 6,Color[0],Renderer[0]);
        SDL_RenderPresent(Renderer[0]);
        // Render Window2
        SDL_SetRenderDrawColor(Renderer[1], Color[2][0], Color[2][1], Color[2][2], Color[2][3]);
        SDL_RenderClear(Renderer[1]);
        SDL_RenderPresent(Renderer[1]);

        SDL_Delay(10);
    }
    SDL_DestroyRenderer(Renderer[0]);
    SDL_DestroyWindow(Window[0]);
    SDL_DestroyRenderer(Renderer[1]);
    SDL_DestroyWindow(Window[1]);
    SDL_Quit();


    return 0;
}

