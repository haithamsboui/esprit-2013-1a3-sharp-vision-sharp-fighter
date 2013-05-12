#ifndef BRAHIM_H_INCLUDED
#define BRAHIM_H_INCLUDED

#include "includes.h"

#define BrahimImageCount 56

IMAGE *BrahimPics[BrahimImageCount];

float xB,yB;
float wB,hB;
int directionB;
int PlayerB;
EtatPlayer etatB;
int IndexB;

void LoadBrahim(int player);

void Draw_Brahim();



#endif // BRAHIM_H_INCLUDED
