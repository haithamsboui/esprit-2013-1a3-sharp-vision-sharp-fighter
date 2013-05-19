#ifndef WASSIM_H_INCLUDED
#define WASSIM_H_INCLUDED

#include "includes.h"
#define WassimImageCount 45

IMAGE *WassimPics[WassimImageCount];

float xW,yW;
float wW,hW;
int directionW;
int PlayerW;
EtatPlayer etatW;
int IndexW;
int IndexCollissionW;
void LoadWassim(int player);

void Draw_Wassim();


#endif // WASSIM_H_INCLUDED
