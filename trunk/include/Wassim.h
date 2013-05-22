#ifndef WASSIM_H_INCLUDED
#define WASSIM_H_INCLUDED

#include "includes.h"
#define WassimImageCount 45

IMAGE *WassimPics[WassimImageCount];

EtatPlayer etatW;

float xW,yW;
float wW,hW;

int directionW;
int PlayerW;
int IndexW;
int IndexCollissionW;
int SuperPowerW;
int FireW;
int ThunderW;
int WindW;
int FreezeW;
void Draw_Wassim();
void LoadWassim(int player);


#endif // WASSIM_H_INCLUDED
