
#define SDL_MAIN_HANDLED
#include "../files-h/includ.h"

SDL_Window *Windows[2];
SDL_Renderer *Renderers[3];

SDL_Window *door;
Rect rects[2]={
    {{480,480},{300,300}},
    {{300,480},{100,300}},
};

int main() {
    char *colorFile = "colors.txt"; 
    int colorRow = 4;
    int Color[colorRow][4];
    colors(colorRow,4, Color, colorFile);

    Player player = {{0, 0}, 
        {60, 60, {400,230}},
        {player.scale.TrueSize.x,
        player.scale.TrueSize.y,}
    };



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
    int mouceX, mouceY;


    if (createWindow(&Windows[0], &Renderers[0], player.window.Width,player.window.Height, 0,0) != 0) {
        return 1;
    }


    if (createWindow(&Windows[1], &Renderers[1], 250, 600, 1920 - 250,0) != 0) {
        SDL_DestroyRenderer(Renderers[0]);
        SDL_DestroyWindow(Windows[0]);
        SDL_Quit();
        return 1;
    }


    if (createWindow(&door, &Renderers[2], doors.scrine.Width, doors.scrine.Height, doors.position.x,doors.position.y) != 0) {
        SDL_DestroyRenderer(Renderers[0]);
        SDL_DestroyWindow(Windows[0]);
        SDL_DestroyRenderer(Renderers[1]);
        SDL_DestroyWindow(Windows[1]);
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
            if (a = _move_Click(a,event, 1, 1) != 0){
                player.position.x = mouceX;
                player.position.y = mouceY;
                a = 0;
            } else{
                player.position.x = player.position.x;
                player.position.y = player.position.y;
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
            collisionScrine(&player, scrinHeight, scrinWidth, &speed);
        }
        SDL_SetWindowPosition(Windows[0], player.position.x, player.position.y);

        SDL_GetMouseState(&mouceX,&mouceY);

        collisionWindow(&player, &doors, &speed, NO_BOUNCE);

        collisionRect(&player, &rects[0], &speed, BOUNCE);
        collisionRect(&player, &rects[1], &speed, BOUNCE);

        setPlayerSide(&player);

        SetRectSide(&rects[0]);
        SetRectSide(&rects[1]);


        SDL_SetWindowAlwaysOnTop(door, SDL_TRUE);

        SDL_SetWindowFullscreen(Windows[1], SDL_WINDOW_FULLSCREEN_DESKTOP);

    // Render  Window1
    SDL_SetRenderDrawColor(Renderers[0], Color[1][0], Color[1][1], Color[1][2], Color[1][3]);
    SDL_RenderClear(Renderers[0]);

    // player render 
    _drawPlayer(player.window.Width/2 - player.scale.Width/2,player.window.Height/2 + player.scale.Height/2 ,speed ,Color[0],Renderers[0], player.scale.Width, player.scale.Height);

    // world render 
    _rectelgle(rects[0].position.x, rects[0].position.y, rects[0].size.Height, rects[0].size.Width, player.position.x, player.position.y, Color[3], Renderers[0], player.window.Width, player.window.Height);
    _rectelgle(rects[1].position.x, rects[1].position.y, rects[1].size.Height, rects[1].size.Width, player.position.x, player.position.y, Color[3], Renderers[0], player.window.Width, player.window.Height);


    SDL_RenderPresent(Renderers[0]);

    SDL_SetRenderDrawColor(Renderers[2], Color[2][0], Color[2][1], Color[2][2], Color[2][3]);
    SDL_RenderClear(Renderers[2]);

    SDL_RenderPresent(Renderers[2]);


    // Render Window2
    SDL_Delay(10);
    }
    SDL_DestroyRenderer(Renderers[0]);
    SDL_DestroyWindow(Windows[0]);
    SDL_DestroyRenderer(Renderers[1]);
    SDL_DestroyWindow(Windows[1]);
    SDL_Quit();


    return 0;
}

