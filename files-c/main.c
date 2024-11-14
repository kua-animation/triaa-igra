
#define SDL_MAIN_HANDLED
#include "../files-h/includ.h"

SDL_Window *Window[2];
SDL_Renderer *Renderer[3];

SDL_Window *door;


void colideScrine(Player *name, int scrineHeight, int scrineWidth, int *speed){
    if (name->window.side.right > scrineWidth){
        name->position.x = scrineWidth - name->window.Width;
        *speed = 0;
    }else if (name->window.side.left < 0){
        name->position.x = 0;
        *speed = 0;
    }

    if (name->window.side.bottom > scrineHeight){
        name->position.y = scrineHeight - name->window.Height;
        *speed = 0;
    }else if (name->window.side.top < 0){
        name->position.y = 0;
        *speed = 0;
    }
}

int main() {
    char *colorFile = "colors.txt"; 
    int colorRow = 4;
    int Color[colorRow][4];
    colors(colorRow,4, Color, colorFile);

    Player player = {{0, 0}, 
    {60, 60, {400,230}},
    {player.scale.TrueSize.x,player.scale.TrueSize.y,}};
    
    int a = 0;
    srand(time(NULL));
    int DoorX = rand() % 1920 + 0;
    int DoorY = rand()% 1080 + 0;

    int speed = 0;
    int index = 0;
    int scrinHeight = 1080;
    int scrinWidth = 1920;


    if (createWindow(&Window[0], &Renderer[0], player.window.Width,player.window.Height, 0,0) != 0) {
        return 1;
    }


    if (createWindow(&Window[1], &Renderer[1], 250, 600, 1920 - 250,0) != 0) {
        SDL_DestroyRenderer(Renderer[0]);
        SDL_DestroyWindow(Window[0]);
        SDL_Quit();
        return 1;
    }


    if (createWindow(&door, &Renderer[2], 100, 100, DoorX,DoorY) != 0) {
        SDL_DestroyRenderer(Renderer[0]);
        SDL_DestroyWindow(Window[0]);
        SDL_DestroyRenderer(Renderer[1]);
        SDL_DestroyWindow(Window[1]);
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
            
            
            //player window size
            if (a = _move_Hold(a, 1, 1) != 0){
                player.window.Height = player.scale.TrueSize.y*2;
                player.window.Width = player.scale.TrueSize.x*2;
                SDL_SetWindowSize(Window[0], player.window.Width, player.window.Height);
                SDL_SetWindowPosition(Window[0], player.position.x, player.position.y);
                a = 0;
            } else{
                player.window.Height = player.scale.TrueSize.y;
                player.window.Width = player.scale.TrueSize.x;
                SDL_SetWindowSize(Window[0], player.window.Width, player.window.Height); 
                SDL_SetWindowPosition(Window[0], player.position.x, player.position.y);
            }

            // axes swich
            if (index = _move_Click(index, event, 1,2) != 0){
                player.position.x -= speed;
                player.position.y += 0;
            } else{
                player.position.y += speed;
                player.position.x += 0;
            }

            speed = _move_Wheel(speed, event, 1);

            if (speed > 5 - (player.window.Width/ player.scale.TrueSize.x)*2){speed = 5 - (player.window.Width / player.scale.TrueSize.x)*2;}
            else if (speed < -5 + (player.window.Width / player.scale.TrueSize.x)*2){speed = -5 + (player.window.Width / player.scale.TrueSize.x)*2;} 
            
            // window colishon 
            colideScrine(&player, scrinHeight, scrinWidth, &speed);
        }
        
        player.window.side.bottom = player.position.y + player.window.Height;
        player.window.side.top = player.position.y;
        player.window.side.left = player.position.x;
        player.window.side.right = player.position.x + player.window.Width;

        SDL_SetWindowAlwaysOnTop(door, SDL_TRUE);

        SDL_SetWindowFullscreen(Window[1], SDL_WINDOW_FULLSCREEN_DESKTOP);


        render (&player,
                speed,Color,
                Renderer);
    }
    SDL_DestroyRenderer(Renderer[0]);
    SDL_DestroyWindow(Window[0]);
    SDL_DestroyRenderer(Renderer[1]);
    SDL_DestroyWindow(Window[1]);
    SDL_Quit();


    return 0;
}

