#ifndef SALAH_H_INCLUDED
#define SALAH_H_INCLUDED

#include "includes.h"


typedef enum {Stable, Forward, Backward,Punch,Kick} EtatPlayer;

IMAGE *SalahPics[51];

float x,y;
float w,h;
int direction;
int Player;
EtatPlayer etat;
int Index;

void LoadSalah(int player);

void Draw_Salah();




#endif // SALAH_H_INCLUDED
