#ifndef BRAHIM_H_INCLUDED
#define BRAHIM_H_INCLUDED

#include "includes.h"

#define BrahimImageCount 56

IMAGE *BrahimPics[BrahimImageCount];

EtatPlayer etatB;

float xB,yB;
float wB,hB;

int directionB;
int PlayerB;
int IndexB;
int IndexCollissionB;
int SuperPowerB;
int FireB;
int ThunderB;
int WindB;
int FreezeB;
void LoadBrahim(int player);
void Draw_Brahim();



#endif // BRAHIM_H_INCLUDED

