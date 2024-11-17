
#define SDL_MAIN_HANDLED
#include "../files-h/includ.h"

SDL_Window *Windows[2];
SDL_Renderer *Renderers[3];

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

int colideWertcle(Player *name, Window *window, int *speed){
    const int buffer = 30;
    if (name->window.side.bottom > window->scrine.side.top + buffer && name->window.side.top < window->scrine.side.bottom - buffer){
        if (name->window.side.right > window->scrine.side.left && name->window.side.left < window->scrine.side.left){
            name->position.x = window->scrine.side.left - name->window.Width;
            *speed = -*speed;
        }
        if (name->window.side.left < window->scrine.side.right && name->window.side.right > window->scrine.side.right){
            name->position.x = window->scrine.side.right;
            *speed = -*speed;
        }
    }if (name->window.side.left < window->scrine.side.right - buffer && name->window.side.right > window->scrine.side.left + buffer){
        if (name->window.side.bottom > window->scrine.side.top && name->window.side.top < window->scrine.side.top){
            name->position.y = window->scrine.side.top - name->window.Height;
            *speed = -*speed;
        }
        if (name->window.side.top < window->scrine.side.bottom && name->window.side.bottom > window->scrine.side.bottom ){
            name->position.y = window->scrine.side.bottom;
            *speed = -*speed;
        }
    }
}

int colideRect(Player *name, Rect *rect, int *speed){
    const int buffer = 10;
    if (name->hitBox.side.bottom > rect->hitBox.top + buffer && name->hitBox.side.top < rect->hitBox.bottom - buffer){
        if (name->hitBox.side.right > rect->hitBox.left && name->hitBox.side.left < rect->hitBox.left){
            name->position.x = rect->hitBox.left - (name->window.Width/2 + name->scale.Width/2);
            *speed = -*speed;
        }
        if (name->hitBox.side.left < rect->hitBox.right && name->hitBox.side.right > rect->hitBox.right){
            name->position.x = rect->hitBox.right - (name->window.Width/2 - name->scale.Width/2);
            *speed = -*speed;

        }
    }if (name->hitBox.side.left < rect->hitBox.right - buffer && name->hitBox.side.right > rect->hitBox.left + buffer){
        if (name->hitBox.side.bottom > rect->hitBox.top && name->hitBox.side.top < rect->hitBox.top){
            name->position.y = rect->hitBox.top - (name->window.Height/2 + name->scale.Height/2);
            *speed = -*speed;
        }
        if (name->hitBox.side.top < rect->hitBox.bottom && name->hitBox.side.bottom > rect->hitBox.bottom ){
            name->position.y = rect->hitBox.bottom - (name->window.Height/2 - name->scale.Height/2);
            *speed = -*speed;
        }
    }
}


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

    Rect rect1={{450,450},
                {300,300}
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
            if (a = _move_Hold(a, 1, 1) != 0){
                player.window.Height = player.scale.TrueSize.y*2;
                player.window.Width = player.scale.TrueSize.x*2;
                SDL_SetWindowSize(Windows[0], player.window.Width, player.window.Height);
                SDL_SetWindowPosition(Windows[0], player.position.x, player.position.y);
                a = 0;
            } else{
                player.window.Height = player.scale.TrueSize.y;
                player.window.Width = player.scale.TrueSize.x;
                SDL_SetWindowSize(Windows[0], player.window.Width, player.window.Height); 
                SDL_SetWindowPosition(Windows[0], player.position.x, player.position.y);
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

        colideWertcle(&player, &doors, &speed);

        colideRect(&player, &rect1, &speed);
        player.window.side.bottom = player.position.y + player.window.Height;
        player.window.side.top = player.position.y;
        player.window.side.left = player.position.x;
        player.window.side.right = player.position.x + player.window.Width;

        player.hitBox.position.x = player.position.x + (player.window.Width/2 - player.scale.Width/2); 
        player.hitBox.position.y = player.position.y + (player.window.Height/2 - player.scale.Height/2);
        player.hitBox.side.bottom = player.hitBox.position.y + player.scale.Height;
        player.hitBox.side.top = player.hitBox.position.y;
        player.hitBox.side.left = player.hitBox.position.x;
        player.hitBox.side.right = player.hitBox.position.x + player.scale.Width;

        rect1.hitBox.bottom = rect1.position.y + rect1.size.Height;
        rect1.hitBox.top = rect1.position.y;
        rect1.hitBox.left = rect1.position.x;
        rect1.hitBox.right = rect1.position.x + rect1.size.Width;

        SDL_SetWindowAlwaysOnTop(door, SDL_TRUE);

        SDL_SetWindowFullscreen(Windows[1], SDL_WINDOW_FULLSCREEN_DESKTOP);


        render (&player,
                speed,Color,
                Renderers);
    }
    SDL_DestroyRenderer(Renderers[0]);
    SDL_DestroyWindow(Windows[0]);
    SDL_DestroyRenderer(Renderers[1]);
    SDL_DestroyWindow(Windows[1]);
    SDL_Quit();


    return 0;
}

