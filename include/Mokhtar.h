#ifndef MOKHTAR_H_INCLUDED
#define MOKHTAR_H_INCLUDED

#define MokhtarImageCount 66


#include "includes.h"


IMAGE *MokhtarPics[MokhtarImageCount];

float xM,yM;
float wM,hM;
int directionM;
int PlayerM;
EtatPlayer etatM;
int IndexM;
int IndexCollissionM;
void LoadMokhtar(int PlayerM);

void Draw_Mokhtar();

#endif // MOKHTAR_H_INCLUDED
