
#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <stdlib.h>
#include "function-h/window.h"
#include "function-h/drawline.h"
#include "function-h/func.h"

SDL_Window *Window[2];
SDL_Renderer *Renderer[2];



int main() {
    char *colorFile = "colors.txt"; 
    int colorRow = 4;
    int Color[colorRow][4];
    colors(colorRow,4, Color, colorFile);


    int PlayerPosX = 0;
    int PlayerPosY = 0;  
    int speed = 0;
    int index = 0;
    int scrinHeight = 1080;
    int scrinWidth = 1920;
    // printf("scrine height in pixles: \n");
    // scanf("%d", &scrinHeight);
    // printf("scrine width in pixles: \n");
    // scanf("%d", &scrinWidth);

    if (createWindow(&Window[0], &Renderer[0], 260,260, 0,0) != 0) {
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
            
            speed = _move_Wheel(speed, event, 1);
            index = _move_Click(index, event, -1,2);
            if (index > 1){ index = 0;}

            if (index == 1){ PlayerPosY += speed /1.2;}
            else if (index == 0){ PlayerPosX -= speed;} 

            if (speed > 5){speed = 5;}
            else if (speed < -5){speed = -5;} 
            
            if (PlayerPosX > scrinWidth - 260){PlayerPosX = scrinWidth - 260;}
            else if (PlayerPosX < 0){PlayerPosX = 0;}
            if (PlayerPosY > scrinHeight - 260){PlayerPosY = scrinHeight - 260;}
            else if (PlayerPosY < 0){PlayerPosY = 0;}

        }
        SDL_SetWindowPosition(Window[0], PlayerPosX, PlayerPosY);
        SDL_SetWindowAlwaysOnTop(Window[0], SDL_TRUE);

        // Render  Window1
        SDL_SetRenderDrawColor(Renderer[0], Color[1][0], Color[1][1], Color[1][2], Color[1][3]);
        SDL_RenderClear(Renderer[0]);
        player(100,120,speed * 6,Color[0],Renderer[0]);
        _rectelgle(500,500,200,200,PlayerPosX,PlayerPosY, Color[3], Renderer[0]);
        _rectelgle(550,550,100,100,PlayerPosX,PlayerPosY, Color[3], Renderer[0]);
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

