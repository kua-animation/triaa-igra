// window.c
#include "../files-h/createWindow.h"

int createWindow(SDL_Window **window, SDL_Renderer **renderer, int sizeX, int sizeY, int posX, int posY) {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    *window = SDL_CreateWindow(NULL,
        posX,
        posY,
        sizeX, sizeY,
        SDL_WINDOW_BORDERLESS);

    if (*window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return 3; 
    }

    *renderer = SDL_CreateRenderer(*window, -1, 0);
    if (*renderer == NULL) {
        printf("Renderer could not be created SDL_Error %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return -1;
    }




    return 0; 
}

