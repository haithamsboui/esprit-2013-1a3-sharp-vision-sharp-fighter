#ifndef SALAH_H_INCLUDED
#define SALAH_H_INCLUDED

#define SalahImageCount 51

#include "includes.h"


typedef enum {Stable, Forward, Backward,Jump,Crouch,Punch,Kick,Fireball,Thunder,Freeze,Wind,Fall,Hit,Defence,Up} EtatPlayer;

IMAGE *SalahPics[SalahImageCount];

EtatPlayer etatS;

float xS,yS;
float wS,hS;

int directionS;
int PlayerS;
int IndexS;
int IndexCollissionS;
int SuperPowerS;

void LoadSalah(int PlayerS);
void Draw_Salah();




#endif // SALAH_H_INCLUDED
