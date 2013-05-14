#ifndef SALAH_H_INCLUDED
#define SALAH_H_INCLUDED

#define SalahImageCount 51

#include "includes.h"


typedef enum {Stable, Forward, Backward,Jump,Crouch,Punch,Kick,Fireball,Thunder,Freeze,Wind,Fall,Hit,Defence,Down} EtatPlayer;

IMAGE *SalahPics[SalahImageCount];

float xS,yS;
float wS,hS;
int directionS;
int PlayerS;
EtatPlayer etatS;
int IndexS;

void LoadSalah(int PlayerS);

void Draw_Salah();




#endif // SALAH_H_INCLUDED
