#ifndef GHOST_H_INCLUDED
#define GHOST_H_INCLUDED

#include "PacMan.h"

enum personality {Blinky, Pinky, Inky, Clyde};

const ink COLOR_BLINKY = red;
const ink COLOR_PINKY = magenta;
const ink COLOR_INKY = cyan;
const ink COLOR_CLYDE = darkyellow;
const ink COLOR_FEAR = blue;
const int GHOST_SIZE = 11;

//Each ghost's initial position and "home"
const point CENTER_BLINKY = point(88,1);
const point CENTER_PINKY  = point(88,88);
const point CENTER_INKY   = point(1,1);
const point CENTER_CLYDE  = point(1,88);

const int ROUTE_SIZE = 4;


class ghost
{
        point loc;
        char pixel[10][GHOST_SIZE][GHOST_SIZE];
        direction dir;
        personality type;
        point target;
        ink color;
        int state;
        //This is the route that Inky will follow.
        point patrolRoute[ROUTE_SIZE] = {point(0,0), point(0,89), point(89,89), point(89,0)};

    public:
        ghost(personality);

        //Changes the ghost's position and state.
        void Move(Plotter&);

        //Undraws the ghost then draws him in his new position.
        void Draw(Plotter&);

        //TEMPORARY
        //Changes state directly.
        void changeState(int);

        //Changes direction directly.
        void direct(direction);

        //Sets the ghost's color.
        void colorize(ink);

        //Reads in the ghost sprites.
        void readSprites();

        //Returns location.
        point getLoc();

        //Sets the ghost's target based on personality as well as the player's
        //direction and location.
        void setTarget(point, direction, int);

        //Changes direction based on target.
        void decideDirection();
};

#endif // GHOST_H_INCLUDED
