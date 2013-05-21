#ifndef MOKHTAR_H_INCLUDED
#define MOKHTAR_H_INCLUDED

#include "includes.h"

#define MokhtarImageCount 66




IMAGE *MokhtarPics[MokhtarImageCount];

EtatPlayer etatM;

float xM,yM;
float wM,hM;

int directionM;
int PlayerM;
int IndexM;
int IndexCollissionM;
int SuperPowerM;

void Draw_Mokhtar();
void LoadMokhtar(int PlayerM);
#endif // MOKHTAR_H_INCLUDED
