#ifndef HAITHAM_H_INCLUDED
#define HAITHAM_H_INCLUDED

#include "includes.h"

#define HaithamImageCount 50

IMAGE *HaithamPics[HaithamImageCount];

float xH,yH;
float wH,hH;
int directionH;
int PlayerH;
EtatPlayer etatH;
int IndexH;

void LoadHaitham(int player);

void Draw_Haitham();


#endif // HAITHAM_H_INCLUDED
