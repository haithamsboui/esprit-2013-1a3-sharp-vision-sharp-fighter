#include "includes.h"

int Intersect(Point pt1,Point pt2,Point pt3,Point pt4)
{
    float A1, A2, B1, B2, C1, C2, det;
    Point inter;
    A1 = pt2.Y - pt1.Y;
    B1 = pt1.X - pt2.X;
    C1 = A1 * pt1.X + B1 * pt1.Y;
    A2 = pt4.Y - pt3.Y;
    B2 = pt3.X - pt4.X;
    C2 = A2 * pt3.X + B2 * pt3.Y;
    det = A1 * B2 - A2 * B1;
    if(det != 0)
    {
        inter.X = (B2 * C1 - B1 * C2) / det;
        inter.Y = (A1 * C2 - A2 * C1) / det;
        if(Min(pt1.X, pt2.X) <= inter.X && Max(pt1.X, pt2.X) >= inter.X &&
                Min(pt1.Y, pt2.Y) <= inter.Y && Max(pt1.Y, pt2.Y) >= inter.Y &&
                Min(pt3.X, pt4.X) <= inter.X && Max(pt3.X, pt4.X) >= inter.X &&
                Min(pt3.Y, pt4.Y) <= inter.Y && Max(pt3.Y, pt4.Y) >= inter.Y)
        {
            return 1;
        }
    }
    return 0;
}

int Collision(Point Shape1[], int n1,Point Shape2[], int n2)
{
    int i,j;
    for(i=0; i<n1; i++)
    {
        for(j=0; j<n2; j++)
        {
            if(Intersect(Shape1[i],Shape1[(i+1)%n1],Shape2[j],Shape2[(j+1)%n2]))
            {
                return 1;
            }
        }
    }
    return 0;
}
