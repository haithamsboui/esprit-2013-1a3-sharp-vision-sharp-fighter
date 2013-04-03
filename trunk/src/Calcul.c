#include "includes.h"

float Percentage(float x)
{
    x= x>100.0f ? 100.0f : x;
    x= x<0.0f ? 0.0f : x;
    return x;
}

float LinearFunc(float start, float end,float percentage)
{
    return ((end-start)*percentage)/100.0f+start;
}

float LaGrange(Pointf points[],int n, float X)
{
    float prod,sum=0;
    int i,j;
    for(i=0; i<n; i++)
    {
        prod = 1;
        for(j=0; j<n; j++)
        {
            if(i!=j)
            {
                prod *= ((X-points[j].x)/(points[i].x-points[j].x));
            }
        }
        sum+=points[i].y*prod;
    }
    return sum;
}
