#ifndef PLAYER_H
#define PLAYER_H



// palyer 
    typedef struct TrueSize{
        int x;
        int y;
    }TrueSize;
    typedef struct Sides{
        int bottom;
        int top; 
        int left;
        int right;
    }Sides;
    typedef struct Scrine{
        int Width;
        int Height;
        Sides side;
    }Scrine;
    typedef struct Position{
        int x;
        int y;
    }Position;
    typedef struct Scale{
        int Width;
        int Height;
        TrueSize TrueSize;
    }Scale;

    typedef struct Palyer{
        Position position;
        Scale scale;
        Scrine window;
        
    }Player;
// main
#endif