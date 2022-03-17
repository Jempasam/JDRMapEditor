#include "CoordCalc.h"

int Coord2::operator[](int i)
{
    if(i==0)return x;
    return y;
}
Coord2::Coord2(int X,int Y){x=X;y=Y;}

Coord2 GetMovementCoord(int Point1x,int Point1y,int Point2x,int Point2y)
{
    bool SigneX=1;bool SigneY=1;
    int X=Point2x-Point1x;int Y=Point2y-Point1y;

    if(X<0){SigneX=0;X*=-1;}if(Y<0){SigneY=0;Y*=-1;}
    int Total=(X+Y);

    X=X*10;Y=Y*10;if(Total!=0){X/=Total;Y/=Total;}


    if(!SigneX)X=X*-1;if(!SigneY)Y=Y*-1;
    return Coord2(X,Y);
}

int getDirectionFromMove(int X,int Y)
{
    int PositiveX;if(X<0)PositiveX=X*-1;else PositiveX=X;
    int PositiveY;if(Y<0)PositiveY=Y*-1;else PositiveY=Y;

    if(PositiveX<=PositiveY){if(Y<0)return 1;if(Y>=0)return 0;}
    else {if(X<0)return 3;if(X>0)return 2;return 0;}
}

int getSpeedFromMove(int X,int Y)
{if(X<0)X*=-1;if(Y<0)Y*=-1;return Y+X;}
