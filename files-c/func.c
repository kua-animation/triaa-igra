#include "../files-h/func.h"
#include <stdio.h>

int colors(int col, int row, int color[row][col], char *name) {
    FILE *file = fopen(name, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            fscanf(file, "%d", &color[i][j]);
        }
    }
    fclose(file);

    return 0;
}

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

