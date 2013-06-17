#ifndef MOKHTAR_H_INCLUDED
#define MOKHTAR_H_INCLUDED

#include "includes.h"

#define MokhtarImageCount 66
#define StableStartM 0
#define StableCountM 4

#define JumpStartM 4
#define JumpCountM 6

#define CrouchStartM 9
#define CrouchCountM 1

#define WalkStartM 63
#define WalkCountM 3

#define PunchStartM 12
#define PunchCountM 3

#define KickStartM 15
#define KickCountM 7

#define FireballStartM 40
#define FireballCountM 9

#define FreezeStartM 49
#define FreezeCountM 5

#define ThunderStartM 59
#define ThunderCountM 4

#define WindStartM 54
#define WindCountM 5

#define DefenceStartM 22
#define DefenceCountM 2

#define FallStartM 25
#define FallCountM 6

#define HitStartM 32
#define HitCountM 3

#define UpStartM 36
#define UpCountM 4




IMAGE *MokhtarPics[MokhtarImageCount];

EtatPlayer etatM;

float xM,yM;
float wM,hM;

int directionM;
int PlayerM;
int IndexM;
int IndexCollissionM;
int SuperPowerM;
int FireM;
int ThunderM;
int WindM;
int FreezeM;

void Draw_Mokhtar(int CPU);
void LoadMokhtar(int PlayerM);
#endif // MOKHTAR_H_INCLUDED
