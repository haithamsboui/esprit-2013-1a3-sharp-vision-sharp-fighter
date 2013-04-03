#ifndef CALCUL_H_INCLUDED
#define CALCUL_H_INCLUDED

#include "includes.h"
//defines a point
typedef struct {
    float x;
    float y;
} Pointf;

// test if number is between 0 and 100
float Percentage(float x);

//return the progress from start to end, according to percentage
float LinearFunc(float start, float end,float percentage);

//Interpolate points to create a smooth function
float LaGrange(Pointf points[],int n, float X);

#endif // CALCUL_H_INCLUDED
