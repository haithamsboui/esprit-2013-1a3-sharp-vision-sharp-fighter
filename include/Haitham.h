#ifndef HAITHAM_H_INCLUDED
#define HAITHAM_H_INCLUDED

#include "includes.h"

#define HaithamImageCount 50
#define StableStartH 0
#define StableCountH 4

#define WalkStartH 4
#define WalkCountH 4

#define KickStartH 8
#define KickCountH 4

#define PunchStartH 12
#define PunchCountH 4

#define FireballStartH 33
#define FireballCountH 4

#define FreezeStartH 37
#define FreezeCountH 3

#define ThunderStartH 40
#define ThunderCountH 7

#define WindStartH 47
#define WindCountH 3

#define DefenceStartH 18
#define DefenceCountH 2

#define CrouchStartH 16
#define CrouchCountH 2

#define JumpStartH 29
#define JumpCountH 4

#define FallStartH 20
#define FallCountH 4

#define HitStartH 27
#define HitCountH 2

#define UpStartH 24
#define UpCountH 3

IMAGE *HaithamPics[HaithamImageCount];

EtatPlayer etatH;

float xH,yH;
float wH,hH;

int directionH;
int PlayerH;
int IndexH;
int IndexCollissionH;
int SuperPowerH;
int FireH;
int ThunderH;
int WindH;
int FreezeH;
void LoadHaitham(int player);
void Draw_Haitham();


#endif // HAITHAM_H_INCLUDED
