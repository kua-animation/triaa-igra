#define SDL_MAIN_HANDLED
#include "../files-h/includ.h"

SDL_Window *Windows[2];
SDL_Renderer *Renderers[3];

SDL_Window *door;
Rect rects[3]={
    {{480,480},{300,300}},
    {{300,480},{100,300}},
    {{580,580},{100,100}},
};

SDL_Event event;

int windowLode(Player *playerName, Window *doorWindow);

void render(Player *playerName, int *speed, int color[4][4], int *world);


int main() {
    char *colorFile = "colors.txt"; 
    int colorRow = 4;
    int Color[colorRow][4];
    colors(colorRow,4, Color, colorFile);

    Player player = {{0, 0}, 
        {60, 60, {250,250}},
        {player.scale.TrueSize.x,
        player.scale.TrueSize.y,}
    };
    int world = 0;

    srand(time(NULL));
    int DoorX = rand() % 1920 + 0;
    int DoorY = rand()% 1080 + 0;
    Window doors = {
        {DoorX, DoorY},
        {400,230,
        {doors.position.y + doors.scrine.Height,
        doors.position.y,
        doors.position.x,
        doors.position.x + doors.scrine.Width}}
    };

    int a = 0;
    int b = 0;

    int speed = 0;
    int index = 0;
    int scrinHeight = 1080;
    int scrinWidth = 1920;

    
    int running = SDL_TRUE;

    windowLode(&player, &doors);

    while (running){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = SDL_FALSE;
                }
            }
            
            
            //player window size
            if (a = _move_Click(a,event, 1, 1) != 0){
                world -= 1;
                a = 0;
            }

            if (b = _move_Hold(b,1,3) != 0){
                player.window.Width = 500;
                player.window.Height = 500;
                b = 0;
            } else {
                player.window.Width = 250;
                player.window.Height = 250;
            }
            speed = 2;

            _move(&player,speed,0,event);

            if (speed > 5 - (player.window.Width/ player.scale.TrueSize.x)*2){speed = 5 - (player.window.Width / player.scale.TrueSize.x)*2;}
            else if (speed < -5 + (player.window.Width / player.scale.TrueSize.x)*2){speed = -5 + (player.window.Width / player.scale.TrueSize.x)*2;} 
            
            // window colishon 
            collisionScrine(&player, scrinHeight, scrinWidth, &speed);
        }
        SDL_SetWindowPosition(Windows[0], player.position.x, player.position.y);

        if (collisionWindow(&player, &doors, &speed, world) != 0){
            world += 1;
            player.position.x = 0;
            player.position.y = 100;
        }

        SDL_SetWindowSize(Windows[0], player.window.Width, player.window.Height);

        setPlayerSide(&player);

        SDL_SetWindowAlwaysOnTop(door, SDL_TRUE);

        SDL_SetWindowFullscreen(Windows[1], SDL_WINDOW_FULLSCREEN_DESKTOP);

        render(&player, &speed, Color, &world);

        
        SDL_Delay(10);
    }
    SDL_DestroyRenderer(Renderers[0]);
    SDL_DestroyWindow(Windows[0]);
    SDL_DestroyRenderer(Renderers[1]);
    SDL_DestroyWindow(Windows[1]);
    SDL_DestroyRenderer(Renderers[2]);
    SDL_DestroyWindow(door);
    SDL_Quit();


    return 0;
}

int windowLode(Player *playerName, Window *doorWindow){
    if (createWindow(&Windows[0], &Renderers[0], playerName->window.Width, playerName->window.Height, 0,0) != 0) {
        return 1;
    }


    if (createWindow(&Windows[1], &Renderers[1], 250, 600, 0,0) != 0) {
        SDL_DestroyRenderer(Renderers[0]);
        SDL_DestroyWindow(Windows[0]);
        SDL_Quit();
        return 1;
    }


    if (createWindow(&door, &Renderers[2], doorWindow->scrine.Width, doorWindow->scrine.Height, doorWindow->position.x,doorWindow->position.y) != 0) {
        SDL_DestroyRenderer(Renderers[0]);
        SDL_DestroyWindow(Windows[0]);
        SDL_DestroyRenderer(Renderers[1]);
        SDL_DestroyWindow(Windows[1]);
        SDL_Quit();
        return 1;
    }
    

}

void worlds(Player *playerName, int *speed, int color[4][4], int str, int end){
    int j = 0;
    int y = 0;
    for(int i = str; i < end; i++){
        if (rects[i].size.Width >= 30 || rects[i].size.Height >= 30){
            _rectelgle(rects[i].position.x, rects[i].position.y, rects[i].size.Height, rects[i].size.Width, playerName->position.x, playerName->position.y, color[3], Renderers[0], playerName->window.Width, playerName->window.Height);
            SetRectSide(&rects[i]);
            y = collisionRect(playerName, &rects[i], speed);
        }
        if ( y > 0){
            *speed = 0;
        }

    }
}

void render(Player *playerName, int *speed, int color[4][4], int *world){
    SDL_SetRenderDrawColor(Renderers[0], color[1][0], color[1][1], color[1][2], color[1][3]);
    SDL_RenderClear(Renderers[0]);
    _drawPlayer(playerName->window.Width/2 - playerName->scale.Width/2,playerName->window.Height/2 + playerName->scale.Height/2 ,speed ,color[0],Renderers[0], playerName->scale.Width, playerName->scale.Height);
    if (*world <= 0){
        worlds(playerName, speed, color, 0, 1);
            
    } else if (*world >= 1){
        worlds(playerName, speed, color, 1, 3);
    } 
    SDL_RenderPresent(Renderers[0]);

    SDL_SetRenderDrawColor(Renderers[2], color[2][0], color[2][1], color[2][2], color[2][3]);
    SDL_RenderClear(Renderers[2]);

    SDL_RenderPresent(Renderers[2]);
        
}

