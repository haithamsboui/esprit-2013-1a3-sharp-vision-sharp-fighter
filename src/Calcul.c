#include "includes.h"

float Percentage(float x)
{
    x= x>100.0f ? 100.0f : x;
    x= x<0.0f ? 0.0f : x;
    return x;
}
