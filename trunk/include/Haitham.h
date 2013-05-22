#ifndef HAITHAM_H_INCLUDED
#define HAITHAM_H_INCLUDED

#include "includes.h"

#define HaithamImageCount 50

IMAGE *HaithamPics[HaithamImageCount];

EtatPlayer etatH;

float xH,yH;
float wH,hH;

int directionH;
int PlayerH;
int IndexH;
int IndexCollissionH;
int SuperPowerH;
int FireH;
int ThunderH;
int WindH;
int FreezeH;
void LoadHaitham(int player);
void Draw_Haitham();


#endif // HAITHAM_H_INCLUDED
