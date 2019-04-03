#include "PacMan.h"
#include <string>
#include <fstream>

using namespace std;

pacman::pacman()
{
    //Initializes all of Pacman's attributes to reasonable values.
    loc.x = CENTER_X;
    loc.y = CENTER_Y;
    dir = EAST;
    color = PACMAN_COLOR;
    mouthState = 0;
    powerPellet = false;
    lives = 3;
}

void pacman::Move(Plotter& g)
{
    //Is Pacman currently opening his mouth or closing it?
    static int mouthCycleDir = -1;

    //Un-draws Pacman
    g.setColor(black);
    switch(dir)
    {
        case NORTH:
            for(int i = loc.x + 3; i < loc.x + 8; ++i)
                g.plot(i, loc.y + PACMAN_SIZE - 1, SQUARE);
            break;
        case WEST:
            for(int i = loc.y + 3; i < loc.y + 8; ++i)
                g.plot(loc.x + PACMAN_SIZE - 1, i, SQUARE);
            break;
        case SOUTH:
            for(int i = loc.x + 3; i < loc.x + 8; ++i)
                g.plot(i, loc.y, SQUARE);
            break;
        case EAST:
            for(int i = loc.y + 3; i < loc.y + 8; ++i)
                g.plot(loc.x, i, SQUARE);
            break;
    }

    switch(dir)
    {
        case NORTH: --loc.y;
                    break;
        case WEST:  --loc.x;
                    break;
        case SOUTH: ++loc.y;
                    break;
        case EAST:  ++loc.x;
                    break;
    }

    //If either fully open or fully closed, start closing/reopening.
    if(mouthState != 1)
        mouthCycleDir = -mouthCycleDir;

    //Update Pacman's mouth state.
    mouthState += mouthCycleDir;

    Draw(g);
}

void pacman::Draw(Plotter& g)
{
    g.setColor(color);
    int p = 3 * dir + mouthState;
    for(int r = 0; r < PACMAN_SIZE; ++r)
    {
        for(int c = 0; c < PACMAN_SIZE; ++c)
        {
            g.plot((loc.x + c), (loc.y + r), pixel[p][r][c]);
        }
    }

}

void pacman::mState(int ms)
{
    mouthState = ms;
}

void pacman::direct(direction dNew)
{
    dir = dNew;
}

void pacman::colorize(ink c)
{
    color = c;
}

void pacman::readSprites()
{
    string line;
    ifstream spriteIn;
    spriteIn.open("ImagePacMan.txt");
    for(int p = 0; p < 12; ++p)
    {
        for(int r = 0; r < PACMAN_SIZE; ++r)
        {
            getline(spriteIn, line);
            for(int c = 0; c < PACMAN_SIZE; ++c)
            {
                if(line[c] == '*')
                    pixel[p][r][c] = SQUARE;
                else
                    pixel[p][r][c] = line[c];
            }
        }
    }
    spriteIn.close();
}

point pacman::getLoc()
{
    return loc;
}

direction pacman::getDir()
{
    return dir;
}
