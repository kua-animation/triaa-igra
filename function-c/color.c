#include "../function-h/color.h"
#include <stdio.h>

int colors(int col, int row, int color[row][col]) {
    FILE *file = fopen("colors.txt", "r");
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
