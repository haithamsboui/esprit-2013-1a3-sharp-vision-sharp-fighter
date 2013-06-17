#ifndef BRAHIM_H_INCLUDED
#define BRAHIM_H_INCLUDED

#include "includes.h"

#define BrahimImageCount 56

#define StableStartB 0
#define StableCountB 4

#define WalkStartB 4
#define WalkCountB 4

#define KickStartB 8
#define KickCountB 5

#define PunchStartB 13
#define PunchCountB 3

#define FireballStartB 16
#define FireballCountB 5

#define FreezeStartB 21
#define FreezeCountB 4

#define ThunderStartB 25
#define ThunderCountB 4

#define WindStartB 29
#define WindCountB 4

#define DefenceStartB 33
#define DefenceCountB 3

#define CrouchStartB 36
#define CrouchCountB 2

#define JumpStartB 38
#define JumpCountB 5

#define FallStartB 43
#define FallCountB 6

#define HitStartB 52
#define HitCountB 4

#define UpStartB 49
#define UpCountB 3

IMAGE *BrahimPics[BrahimImageCount];

EtatPlayer etatB;

float xB,yB;
float wB,hB;

int directionB;
int PlayerB;
int IndexB;
int IndexCollissionB;
int SuperPowerB;
int FireB;
int ThunderB;
int WindB;
int FreezeB;
void LoadBrahim(int player);
void Draw_Brahim(int CPU);



#endif // BRAHIM_H_INCLUDED

