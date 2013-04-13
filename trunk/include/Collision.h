#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED

#include "includes.h"

#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)

typedef struct
{
    float X;
    float Y;
} Point;

//Intersection of two lines
int Intersect(Point pt1,Point pt2,Point pt3,Point pt4);
//Intersection of two shapes
int Collision(Point Shape1[], int n1,Point Shape2[], int n2);


#endif // COLLISION_H_INCLUDED
