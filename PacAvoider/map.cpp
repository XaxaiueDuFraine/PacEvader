#include "map.h"

void pacmanMap::Draw()
{
    int xCounter = 0, yCounter = 0, permaYCounter = 0;

    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            if(pacmap[i][j] == 0)
            {
                for(int x = 0; x < 13; x++)
                {
                    for(int y = 0; y < 13; y++)
                    {
                        mapG.plot(xCounter, yCounter, ' ');
                        yCounter++;
                    }
                    xCounter++;
                    yCounter = permaYCounter;
                }

            }
            else if(pacmap[i][j] == 1)
            {
                for(int x = 0; x < 13; x++)
                {
                    for(int y = 0; y < 13; y++)
                    {
                        mapG.plot(xCounter, yCounter, SQUARE);
                        yCounter++;
                    }
                    xCounter++;
                    yCounter = permaYCounter;
                }

            }


        }
        xCounter = 0;
        permaYCounter += 13;
    }
}
