#include "plotter.h"
#include "Ghost.h"
#include <string>
#include <fstream>

using namespace std;

ghost::ghost(personality p)
{
    //Initializes all of the ghost's attributes to reasonable values based on personality.
    dir = EAST;
    type = p;
    state = 0;
    switch(type)
    {
        case Blinky:
            color = COLOR_BLINKY;
            loc = CENTER_BLINKY;
            break;
        case Pinky:
            color = COLOR_PINKY;
            loc = CENTER_PINKY;
            break;
        case Inky:
            color = COLOR_INKY;
            loc = CENTER_INKY;
            break;
        case Clyde:
            color = COLOR_CLYDE;
            loc = CENTER_CLYDE;
            break;
    }
}

/* This function undraws, moves, and redraws the ghost.
 * Target and direction should be decided before it is called.
 */
void ghost::Move(Plotter& g)
{

    //Un-draws the ghost
    g.setColor(black);
    switch(dir)
    {
        case NORTH:
            for(int i = loc.x; i < loc.x + GHOST_SIZE; ++i)
                g.plot(i, loc.y + GHOST_SIZE - 1, SQUARE);
            break;
        case WEST:
            for(int i = loc.y; i < loc.y + GHOST_SIZE; ++i)
                g.plot(loc.x + GHOST_SIZE - 1, i, SQUARE);
            break;
        case SOUTH:
            for(int i = loc.x; i < loc.x + GHOST_SIZE; ++i)
                g.plot(i, loc.y, SQUARE);
            break;
        case EAST:
            for(int i = loc.y; i < loc.y + GHOST_SIZE; ++i)
                g.plot(loc.x, i, SQUARE);
            break;
    }

    //Moves the ghost
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

    //Update the ghost's state.
    if(state == 0)
        ++state;
    else
        --state;

    Draw(g);
}

void ghost::Draw(Plotter& g)
{
    g.setColor(color);
    int p = 2 * dir + state;
    for(int r = 0; r < GHOST_SIZE; ++r)
    {
        for(int c = 0; c < GHOST_SIZE; ++c)
        {
            g.plot((loc.x + c), (loc.y + r), pixel[p][r][c]);
        }
    }

}

void ghost::changeState(int ms)
{
    state = ms;
}

void ghost::direct(direction dNew)
{
    dir = dNew;
}

void ghost::colorize(ink c)
{
    color = c;
}

void ghost::readSprites()
{
    string line;
    ifstream spriteIn;
    spriteIn.open("ImageGhost.txt");
    for(int p = 0; p < 10; ++p)
    {
        for(int r = 0; r < GHOST_SIZE; ++r)
        {
            getline(spriteIn, line);
            for(int c = 0; c < GHOST_SIZE; ++c)
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

point ghost::getLoc()
{
    return loc;
}

/*
This function contains the logic that decides the ghosts' targets.
This results in different behavior based on each ghost's type.
*/
void ghost::setTarget(point pac, direction pacDir, int cycle)
{
    static int progress = 0;
    point newTarget;

    switch(type)
    {
        case Blinky:
            if((cycle % 900) >= 700)
            {
                newTarget = CENTER_BLINKY;
            }
            else
            {
                newTarget = pac;
            }
            break;

        case Pinky:
            if((cycle % 900) >= 700)
            {
                newTarget = CENTER_PINKY;
            }
            else
            {
                switch(pacDir)
                {
                    case NORTH:
                        newTarget.x = pac.x;
                        newTarget.y = pac.y - 40;
                        break;
                    case WEST:
                        newTarget.x = pac.x - 40;
                        newTarget.y = pac.y;
                        break;
                    case SOUTH:
                        newTarget.x = pac.x;
                        newTarget.y = pac.y + 40;
                        break;
                    case EAST:
                        newTarget.x = pac.x + 40;
                        newTarget.y = pac.y;
                        break;
                }
            }
            break;

        case Inky:
            if((cycle % 900) >= 700)
            {
                newTarget = CENTER_INKY;
            }
            else if(loc.distance(pac) < 40)
            {
                newTarget = pac;
            }
            else
            {
                newTarget = patrolRoute[progress];
                if(loc.distance(patrolRoute[progress]) < 3)
                    progress = (progress + 1) % ROUTE_SIZE;
            }
            break;

        case Clyde:
            if((cycle % 900) >= 700)
            {
                newTarget = CENTER_CLYDE;
            }
            else if(loc.distance(pac) < 25)
            {
                newTarget = CENTER_CLYDE;
            }
            else
            {
                newTarget = pac;
            }
            break;
    }

    target = newTarget;
}

void ghost::decideDirection()
{
    double distN = 100000, distW = 100000, distS = 100000, distE = 100000;
    bool nValid = true, wValid = true, sValid = true, eValid = true;

    if(dir == SOUTH || loc.y <= 0)
        nValid = false;
    if(dir == EAST || loc.x <= 0)
        wValid = false;
    if(dir == NORTH || loc.y >= 89)
        sValid = false;
    if(dir == WEST || loc.x >= 89)
        eValid = false;

    if(nValid)
        distN = target.distance(loc.x, loc.y - 1);
    if(wValid)
        distW = target.distance(loc.x - 1, loc.y);
    if(sValid)
        distS = target.distance(loc.x, loc.y + 1);
    if(eValid)
        distE = target.distance(loc.x + 1, loc.y);

    if(distN <= distW && distN <= distS && distN <= distE)
        direct(NORTH);
    else if(distW <= distS && distW <= distE)
        direct(WEST);
    else if(distS <= distE)
        direct(SOUTH);
    else
        direct(EAST);
}
