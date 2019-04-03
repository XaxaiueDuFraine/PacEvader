#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cmath>
#include "PacMan.h"
#include "Ghost.h"

using namespace std;

const int TITLE_HEIGHT = 11;
const int TITLE_WIDTH = 100;

int delay = 60;

void printTitle(Plotter);
void eraseTitle(Plotter);

bool menu(Plotter);

int main()
{
    pacman player;
    ghost g[4] = {ghost(Blinky), ghost(Pinky), ghost(Inky), ghost(Clyde)};
    Plotter gr;
    int moveCycle = 0;
    unsigned int score = 0;
    point playerLoc, ghostLoc;
    direction nextDir = EAST;
    point testPoint;

    bool quit = menu(gr);
    int n;
    char c;

    player.readSprites();
    player.Draw(gr);

    g[0].readSprites();
    g[0].Draw(gr);
    g[1].readSprites();
    g[1].Draw(gr);
    g[2].readSprites();
    g[2].Draw(gr);
    g[3].readSprites();
    g[3].Draw(gr);

    while(!quit)
    {
        Sleep(delay);
        testPoint = player.getLoc();
        if(player.getDir() == NORTH)
        {
            if(player.getLoc().getY() > 0)
                player.Move(gr);
        }
        else if(player.getDir() == WEST)
        {
            if(player.getLoc().getX() > 0)
                player.Move(gr);
        }
        else if(player.getDir() == SOUTH)
        {
            if(player.getLoc().getY() < 89)
                player.Move(gr);
        }
        else if(player.getDir() == EAST)
        {
            if(player.getLoc().getX() < 89)
                player.Move(gr);
        }

        if(kbhit())
        {
            c = getch();
            n = c;

            if(n == -32)
            {
                n = getch();
                switch(n)
                {
                    case 72: //player.direct(NORTH);
                             nextDir = NORTH;
                        break;
                    case 75: //player.direct(WEST);
                             nextDir = WEST;
                        break;
                    case 80: //player.direct(SOUTH);
                             nextDir = SOUTH;
                        break;
                    case 77: //player.direct(EAST);
                             nextDir = EAST;
                }
            }
            else
            {
                if(c == 'q')
                    quit = true;
            }
        }

        g[0].decideDirection();
        g[1].decideDirection();
        g[2].decideDirection();
        g[3].decideDirection();

        player.direct(nextDir);

        if(moveCycle > 0)
        {
            g[0].setTarget(player.getLoc(), player.getDir(), score);
            g[1].setTarget(player.getLoc(), player.getDir(), score);
            g[2].setTarget(player.getLoc(), player.getDir(), score);
            g[3].setTarget(player.getLoc(), player.getDir(), score);

            g[0].Move(gr);
            g[1].Move(gr);
            g[2].Move(gr);
            g[3].Move(gr);
        }


        playerLoc = player.getLoc();
        for(int i = 0; i <= 3; ++i)
        {
            ghostLoc = g[i].getLoc();
            if(playerLoc.distance(ghostLoc) < 8)
                quit = true;
        }

        moveCycle = (moveCycle + 1) % 2;
        ++score;

        gr.setColor(green);
        gr.plot(0, 0, '#');
        cout << score;
    }

    gr.setColor(green);
    gr.plot(0, 50, '#');
    cout << "You avoided the ghosts for " << score << " cycles.";

    return 0;
}

void printTitle(Plotter g)
{
    char pixel[TITLE_HEIGHT][TITLE_WIDTH];

    string line;
    ifstream spriteIn;
    spriteIn.open("Title.txt");

    for(int r = 0; r < TITLE_HEIGHT; ++r)
    {
        getline(spriteIn, line);
        for(int c = 0; c < TITLE_WIDTH; ++c)
        {
            if(line[c] == '*')
                pixel[r][c] = SQUARE;
            else
                pixel[r][c] = line[c];
        }
    }

    spriteIn.close();

    for(int r = 0; r < TITLE_HEIGHT; ++r)
    {
        for(int c = 0; c < TITLE_WIDTH; ++c)
        {
            g.plot(c, r, pixel[r][c]);
        }
    }
}

void eraseTitle(Plotter g)
{
    g.setColor(black);

    for(int r = 0; r < TITLE_HEIGHT + 10; ++r)
    {
        for(int c = 0; c < TITLE_WIDTH; ++c)
        {
            g.plot(c,r,SQUARE);
        }
    }
}

bool menu(Plotter g)
{
    char input;
    bool quit = false;
    bool exit = false;

    printTitle(g);
    cout << endl;
    cout << "Welcome to Pac-Evader!" << endl;

    while(!quit)
    {
        bool valid = false;

        printTitle(g);
        cout << endl;
        cout << "Welcome to Pac-Evader!" << endl;

        cout << "1: Play" << endl
             << "2: Set Game Speed" << endl
             << "3: Quit" << endl;

        while(!valid)
        {
            input = getch();

            if(input == '1')
            {
                valid = true;
                quit = true;
            }
            else if(input == '2')
            {
                valid = true;

                cout << "Choose speed:" << endl
                     << "1: Very Slow" << endl
                     << "2: Slow" << endl
                     << "3: Normal" << endl
                     << "4: Fast" << endl
                     << "5: Very Fast" << endl
                     << "6: Going to Plaid" << endl;

                input = getch();

                switch(input)
                {
                    case '1': delay = 180;
                        break;
                    case '2': delay = 120;
                        break;
                    case '3': delay = 60;
                        break;
                    case '4': delay = 30;
                        break;
                    case '5': delay = 10;
                        break;
                    case '6': delay = 1;
                        break;
                    default: delay = 60;
                }

                g.setColor(black);

                for(int r = 16; r < 23; ++r)
                {
                    for(int c = 0; c < 20; ++c)
                    {
                        g.plot(c,r,SQUARE);
                    }
                }

                g.setColor(green);
            }
            else if(input == '3')
            {
                valid = true;
                quit = true;
                exit = true;
            }
        }
    }

    eraseTitle(g);

    return exit;
}
