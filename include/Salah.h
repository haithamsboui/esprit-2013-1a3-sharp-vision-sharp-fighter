#ifndef SALAH_H_INCLUDED
#define SALAH_H_INCLUDED

#define SalahImageCount 51

#include "includes.h"


typedef enum {Stable, Forward, Backward,Jump,Crouch,Punch,Kick,Fireball,Thunder,Freeze,Wind,Fall,Hit,Defence,Down} EtatPlayer;

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
