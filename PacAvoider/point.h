#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

struct point
{
        int x, y;

        point();
        point(int, int);

        int getX() const;
        int getY() const;
        void setX(int);
        void setY(int);

        double distance(point);
        double distance(int, int);
};

#endif // POINT_H_INCLUDED
