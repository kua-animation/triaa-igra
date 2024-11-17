#ifndef STRUCT_H
#define STRUCT_H



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
    typedef struct Scales{
        int Width;
        int Height;
        TrueSize TrueSize;
    }Scales;

    typedef struct Scale{
        int Width;
        int Height;
    }Scale;
    typedef struct HitBox{
        Position position;
        Sides side;
    }HitBox;
    typedef struct Palyer{
        Position position;
        Scales scale;
        Scrine window;
        HitBox hitBox;
    }Player;

    typedef struct Window{
        Position position;
        Scrine scrine;
    }Window;

    typedef struct Rect{
        Position position;
        Scale size;
        Sides hitBox;
    }Rect;

// main
#endif