#include "includes.h"

int Random(int min, int max)
{
    srand (time(NULL));
    return rand() % (max-min+1) + min;
}

float Percentage(float x)
{
    return Max(Min(x,100.0f),0.0f);
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
