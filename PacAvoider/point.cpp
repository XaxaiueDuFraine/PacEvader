#include "point.h"
#include <cmath>

point::point()
{
    x = 0;
    y = 0;
}

point::point(int a, int b)
{
    x = a;
    y = b;
}

int point::getX() const
{
    return x;
}

int point::getY() const
{
    return y;
}

void point::setX(int n)
{
    x = n;
}

void point::setY(int n)
{
    y = n;
}

double point::distance(point other)
{
    double dist = sqrt((x - other.x) * (x - other.x) + (y - other.y)  * (y - other.y));
    return dist;
}

double point::distance(int otherX, int otherY)
{
    double dist = sqrt((x - otherX) * (x - otherX) + (y - otherY)  * (y - otherY));
    return dist;
}
