#ifndef SALAH_H_INCLUDED
#define SALAH_H_INCLUDED

#define SalahImageCount 51
#define StableStartS 0
#define StableCountS 3

#define JumpStartS 3
#define JumpCountS 4

#define CrouchStartS 7
#define CrouchCountS 2

#define WalkStartS 9
#define WalkCountS 3

#define PunchStartS 14
#define PunchCountS 5

#define KickStartS 19
#define KickCountS 4

#define FireballStartS 33
#define FireballCountS 5

#define FreezeStartS 38
#define FreezeCountS 4

#define ThunderStartS 42
#define ThunderCountS 5

#define WindStartS 47
#define WindCountS 4

#define DefenceStartS 12
#define DefenceCountS 2

#define FallStartS 26
#define FallCountS 4

#define HitStartS 23
#define HitCountS 2

#define UpStartS 30
#define UpCountS 3

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
int FireS;
int ThunderS;
int WindS;
int FreezeS;

void LoadSalah(int PlayerS);
void Draw_Salah();




#endif // SALAH_H_INCLUDED
