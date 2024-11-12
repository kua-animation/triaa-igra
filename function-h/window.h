// window.h
#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>  // Include SDL header
#include <stdio.h>     // Include stdio for printf

// Function declaration
int _createWindow();

// External variables for window and renderer
extern SDL_Window *window;
extern SDL_Renderer *renderer;

#endif // WINDOW_H
