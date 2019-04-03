#ifndef PACMAN_H_INCLUDED
#define PACMAN_H_INCLUDED

#include "plotter.h"
#include "point.h"

enum direction {NORTH, WEST, SOUTH, EAST};

const ink PACMAN_COLOR = yellow;
const int PACMAN_SIZE = 11;
const int CENTER_X = 50;
const int CENTER_Y = 50;

class pacman
{
        point loc;
        char pixel[12][PACMAN_SIZE][PACMAN_SIZE];
        direction dir;
        ink color;
        int mouthState;
        bool powerPellet;
        int lives;

    public:
        pacman();

        //Changes Pacman's position and mouth state.
        void Move(Plotter&);

        //Undraws Pacman then draws him in his new position.
        void Draw(Plotter&);

        //Changes Pacman's current number of lives. Takes an integer, logically
        //either 1 or -1, and adds it to the current lives, then returns lives.
        int  getALife(int);

        //TEMPORARY
        //Changes mouth state directly.
        void mState(int);

        //TEMPORARY
        //Changes direction directly.
        void direct(direction);

        //Sets Pacman's color.
        void colorize(ink);

        //Reads in the Pacman sprites once, so it doesn't have to be done
        //before every draw.
        void readSprites();

        //Returns location.
        point getLoc();

        //Returns direction.
        direction getDir();
};

#endif // PACMAN_H_INCLUDED
