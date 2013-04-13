#ifndef SALAH_H_INCLUDED
#define SALAH_H_INCLUDED

#include "includes.h"

#define Salah(file) "Resources/Images/Salah/" #file

typedef enum {Stable, Forward, Backward,Punch,Kick} EtatSalah;

IMAGE *SalahPics[51];

float x,y;
float w,h;
int direction;
int Player;
EtatSalah etat;
int Index;

void LoadSalah(int player);

void Draw_Salah();




#endif // SALAH_H_INCLUDED
