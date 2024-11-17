// window.h
#ifndef CREATEWINDOW_H
#define CREATEWINDOW_H

#include <SDL2/SDL.h>  // Include SDL header
#include <stdio.h>     // Include stdio for printf

// Function declaration
int createWindow(SDL_Window **window, SDL_Renderer **renderer, int sizeX, int sizeY, int posX, int posY);


#endif // WINDOW_H
