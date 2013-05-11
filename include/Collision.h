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

Point **SalahCollision;
Point **HaithamCollision;

int ProcessCollision(IMAGE ** pics1, int index1, Point **Data1,float x1,float y1,float w1,float h1,
                     IMAGE ** pics2, int index2, Point **Data2,float x2,float y2,float w2,float h2);
//Intersection of two lines
int Intersect(Point pt1,Point pt2,Point pt3,Point pt4);
//Intersection of two shapes
//int Collision(Point Shape1[], int n1,Point Shape2[], int n2);

void LoadCollisionData();

void UnLoadCollisionData();


#endif // COLLISION_H_INCLUDED
