#include "../files-h/player.h"

int collisionRect(Player *name, Rect *rect, int *speed, int bounce){
    const int buffer = 10;

    switch (bounce)
    {
    case BOUNCE:
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
    break;
    case NO_BOUNCE:
    if (name->hitBox.side.bottom > rect->hitBox.top + buffer && name->hitBox.side.top < rect->hitBox.bottom - buffer){
        if (name->hitBox.side.right > rect->hitBox.left && name->hitBox.side.left < rect->hitBox.left){
            name->position.x = rect->hitBox.left - (name->window.Width/2 + name->scale.Width/2);
            *speed = 0;
        }
        if (name->hitBox.side.left < rect->hitBox.right && name->hitBox.side.right > rect->hitBox.right){
            name->position.x = rect->hitBox.right - (name->window.Width/2 - name->scale.Width/2);
            *speed = 0;

        }
    }if (name->hitBox.side.left < rect->hitBox.right - buffer && name->hitBox.side.right > rect->hitBox.left + buffer){
        if (name->hitBox.side.bottom > rect->hitBox.top && name->hitBox.side.top < rect->hitBox.top){
            name->position.y = rect->hitBox.top - (name->window.Height/2 + name->scale.Height/2);
            *speed = 0;
        }
        if (name->hitBox.side.top < rect->hitBox.bottom && name->hitBox.side.bottom > rect->hitBox.bottom ){
            name->position.y = rect->hitBox.bottom - (name->window.Height/2 - name->scale.Height/2);
            *speed = 0;
        }
    }
    break;
    default:
    break;
    }
}

void collisionScrine(Player *name, int scrineHeight, int scrineWidth, int *speed){
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

int collisionWindow(Player *name, Window *window, int *speed, int bounce){
    const int buffer = 30;

        switch (bounce)
    {
    case BOUNCE:
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
    break;
    case NO_BOUNCE:
        if (name->window.side.bottom > window->scrine.side.top + buffer && name->window.side.top < window->scrine.side.bottom - buffer){
            if (name->window.side.right > window->scrine.side.left && name->window.side.left < window->scrine.side.left){
                name->position.x = window->scrine.side.left - name->window.Width;
                *speed = 0;
            }
            if (name->window.side.left < window->scrine.side.right && name->window.side.right > window->scrine.side.right){
                name->position.x = window->scrine.side.right;
                *speed = 0;
            }
        }if (name->window.side.left < window->scrine.side.right - buffer && name->window.side.right > window->scrine.side.left + buffer){
            if (name->window.side.bottom > window->scrine.side.top && name->window.side.top < window->scrine.side.top){
                name->position.y = window->scrine.side.top - name->window.Height;
                *speed = 0;
            }
            if (name->window.side.top < window->scrine.side.bottom && name->window.side.bottom > window->scrine.side.bottom ){
                name->position.y = window->scrine.side.bottom;
                *speed = 0;
            }
        }
    break;
    default:
    break;
    }
}

void setPlayerSide(Player *name){
    name->window.side.bottom = name->position.y + name->window.Height;
    name->window.side.top = name->position.y;
    name->window.side.left = name->position.x;
    name->window.side.right = name->position.x + name->window.Width;

    name->hitBox.position.x = name->position.x + (name->window.Width/2 - name->scale.Width/2); 
    name->hitBox.position.y = name->position.y + (name->window.Height/2 - name->scale.Height/2);
    name->hitBox.side.bottom = name->hitBox.position.y + name->scale.Height;
    name->hitBox.side.top = name->hitBox.position.y;
    name->hitBox.side.left = name->hitBox.position.x;
    name->hitBox.side.right = name->hitBox.position.x + name->scale.Width;
}

