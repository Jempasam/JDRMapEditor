#ifndef COORDCALC_H_INCLUDED
#define COORDCALC_H_INCLUDED

#include <iostream>

class Coord2
{
    public:
    int x=0;int y=0;

    Coord2(int X=0,int Y=0);
    int operator[](int i);
};
Coord2 GetMovementCoord(int Point1x,int Point1y,int Point2x,int Point2y);
int getDirectionFromMove(int X,int Y);
int getSpeedFromMove(int X,int Y);

#endif // COORDCALC_H_INCLUDED
